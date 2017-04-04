/* Sample UDP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define portnumber 6012

int main(void)
{
   int sockfd,n;
   //int portnumber;
   struct sockaddr_in6 servaddr,cliaddr;
   socklen_t len;
   char mesg[1024];


  /* if (argc !=2){
	printf("ERROR: No ports provided\n");

   }*/

   sockfd=socket(AF_INET6,SOCK_DGRAM,0);

   if (sockfd < 0){
	printf("ERROR: Socket could not be created\n");

   }

  // portnumber=atoi(argv[1]);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin6_family = AF_INET6;
   servaddr.sin6_addr=in6addr_any;
   servaddr.sin6_port=htons((unsigned short )portnumber);
   if (bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
     printf("ERROR: Binding failed\n");   
   }
   else printf ("SERVER READY\n");

   for (;;)
   {
      len = sizeof(cliaddr);
      n = recvfrom(sockfd,mesg,1024,0,(struct sockaddr *)&cliaddr,&len);
      sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
      printf("-------------------------------------------------------\n");
      mesg[n] = 0;
      printf("Received the following:\n");
      printf("%s\n",mesg);
      printf("-------------------------------------------------------\n");
   }
}

