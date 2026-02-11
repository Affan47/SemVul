connectPmd()
{
   int sock ;
   u_long pmd_host ;
   struct hostent *host ;

   if (isdigit(PMD_HOST[0]))
      pmd_host = inet_addr(PMD_HOST) ;
   else
    {
       if ((host = gethostbyname(PMD_HOST)) == NULL)
	{
	   printf("connectPmd::gethostbyname\n") ;
	   exit(1) ;
	}
       pmd_host = *((long *)host->h_addr_list[0]) ;
    }

   if ((sock = get_socket()) == -1)
    {
       printf("connectPmd::get_socket\n") ;
       exit(1) ;
    }
   if (!do_connect(sock, pmd_host, htons(PMD_PORT)))
    {
       printf("connectPmd::do_connect\n") ;
       exit(1) ;
    }
   return sock ;
}
