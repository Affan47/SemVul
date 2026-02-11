srstatfs64(s)
int     s;
{
   int status = 0 ;
   int rcode = 0;
   int len ;
   char *p ;
   char path[MAXFILENAMSIZE] ;
   struct rfstatfs64 statfsbuf ;

#if defined(_WIN32)
   struct thData *td;
   td = (struct thData*)TlsGetValue(tls_i);
#endif

   p= rqstbuf + 2*WORDSIZE ;
   unmarshall_LONG(p,len) ;
   if ( (status = srchkreqsize(s,p,len)) == -1 ) {
     rcode = errno;
   } else {
     log(LOG_DEBUG,"srstatfs64(): reading %d bytes\n",len) ;
     serrno = 0;
     if ((status = netread_timeout(s,rqstbuf,len,RFIO_CTRL_TIMEOUT)) != len) {
       log(LOG_ERR,"srstatfs64(): read(): %s\n", neterror());
       return -1;
     }

     p= rqstbuf ;
     status = 0;
     *path = '\0';
     if (unmarshall_STRINGN(p, path, MAXFILENAMSIZE) == -1 ) {
       if (status == 0) {
         status = -1 ;
         rcode = SENAMETOOLONG;
       }
     }
     if ( !status ) {
       status = rfstatfs64(path,&statfsbuf) ;
       rcode = errno ;
       log(LOG_INFO,"srstatfs64: path : %s , status %d\n",path,status ) ;
     }


   }

   p = rqstbuf ;
   marshall_LONG( p, statfsbuf.bsize ) ;
   marshall_HYPER( p, statfsbuf.totblks ) ;
   marshall_HYPER( p, statfsbuf.freeblks ) ;
   marshall_HYPER( p, statfsbuf.totnods ) ;
   marshall_HYPER( p, statfsbuf.freenods ) ;
   marshall_LONG( p, status ) ;
   marshall_LONG( p, rcode ) ;

   log(LOG_DEBUG, "srstatfs64: sending back %d\n", status);
   serrno = 0;
   if (netwrite_timeout(s,rqstbuf,3*LONGSIZE+4*HYPERSIZE,RFIO_CTRL_TIMEOUT) != (3*LONGSIZE+4*HYPERSIZE))  {
      log(LOG_ERR, "srstatfs64: netwrite_timeout(): %s\n", neterror());
      return -1 ;
   }
   return status ;
}
