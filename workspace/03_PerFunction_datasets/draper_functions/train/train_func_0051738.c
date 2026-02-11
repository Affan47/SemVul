kill_old_cid(cidport)
sng_int16 cidport;
{
   cid_exit_ot in ;
   int sock ;
   u_long cid_host ;
   struct hostent *host ;
   char host_name[MAP_LEN];
   u_short this_op = CID_OP_EXIT;

   alarm(15);

   gethostname(host_name,sizeof(host_name));
   if (isdigit(host_name[0]))
      cid_host = inet_addr(host_name) ;
   else
    {
       if ((host = gethostbyname(host_name)) == NULL)
        {
           printf("Error: gethostbyname.\n") ;
           exit(1) ;
        }
       cid_host = *((long *)host->h_addr_list[0]) ;
    }

   if ((sock = get_socket()) == -1)
    {
       printf("Error: Cannot get socket.\n") ;
       exit(1) ;
    }
   if (!do_connect(sock, cid_host, cidport))
    {


        return;
    }
   printf("Found an old CID. \n");

   this_op = htons(this_op);
   if (!writen(sock, (char *)&this_op, sizeof(u_short)))
   {
        printf("Found a malfunctioning CID ...\n");
        return;
   }

   if (!readn(sock, (char *)&in, sizeof(cid_exit_ot)))
    {
       printf("Found a malfunctioning CID ...\n") ;
       return ;
    }
   printf("Removed an old CID \n");
   return;
}
