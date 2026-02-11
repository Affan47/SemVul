main_loop (int local_in, int local_out, int sock) {
 int    len = 1;
 char   buf[1024];
 fd_set sl;
 struct timeval tv;
 int maxfh = (local_in > sock ? local_in : sock) + 1;

 while (len > 0) {
  FD_ZERO(&sl);
  FD_SET(local_in, &sl);
  FD_SET(sock, &sl);

  tv.tv_sec  = 1;
  tv.tv_usec = 0;

  if (select(maxfh, &sl, NULL, NULL, &tv) > 0) {
   if ( FD_ISSET(sock, &sl) ) {
    if ( (len = read(sock, buf, 1024)) == -1 )
     return -1;
    if ( write(local_out, buf, len) != len )
     return -1;
   } else {
    if ( (len = read(local_in, buf, 1024)) == -1 )
     return -1;
    if ( write(sock, buf, len) != len )
     return -1;
   }
  }
 }
 return 0;
}
