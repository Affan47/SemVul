open_socket(int port_number)
{
 struct sockaddr_in sin ;
 struct linger lingeropt ;
 int flag2 ;
 int itry;
 socklen_t j ;

 client_connected = 0 ;


 fd = socket(AF_INET, SOCK_STREAM, 0);
 if(fd < 0)
 {
  perror("socket");
  return -1;
 }


 memset (&sin, 0, sizeof(struct sockaddr_in)) ;
 sin.sin_addr.s_addr = INADDR_ANY;
 sin.sin_family      = AF_INET;
 sin.sin_port        = htons(port_number);
 flag2 = 1 ;
 j = sizeof(int) ;
 setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag2, j) ;
 j = sizeof(struct linger) ;
 getsockopt(fd, SOL_SOCKET, SO_LINGER, &lingeropt, &j) ;
 if (lingeropt.l_onoff)
 {
  fprintf(stderr, "Setting linger option\n") ;
  lingeropt.l_onoff = 0 ;
  lingeropt.l_linger = 0 ;
  j = sizeof(struct linger) ;
  setsockopt(fd, SOL_SOCKET, SO_LINGER, &lingeropt, j) ;
 }


 for (itry=0; itry < 50; itry++)
 {
  if(bind(fd, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0)
  {
   syslog(LOG_ERR, "Bind error, retry in 6 seconds.\n");
   fprintf(stderr, "Bind error, retry in 6 seconds.\n");
   sleep(6);
  }
  else break;
 }
 if (itry == 50)
 {
  perror("bind");
  return -1;
 }


 if( listen(fd, 1) < 0)
 {
  perror("listen");
  return -1;
 }

 return fd;
}
