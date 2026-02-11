srclose_v3(s, infop, fd)
SOCKET  s;
int     fd;
struct rfiostat *infop;
{
   int  status;
   int  rcode;
   char *p;
   char tmpbuf[21], tmpbuf2[21];

#if defined(_WIN32)
   struct thData *td;
   td = (struct thData*)TlsGetValue(tls_i);
#endif

   log(LOG_INFO,"%d read, %d readahead, %d write, %d flush, %d stat, %d lseek and %d preseek\n",
       myinfo.readop, myinfo.aheadop, myinfo.writop, myinfo.flusop, myinfo.statop,
       myinfo.seekop, myinfo.presop);
   log(LOG_INFO,"%s bytes read and %s bytes written\n",
      u64tostr(myinfo.rnbr,tmpbuf,0), u64tostr(myinfo.wnbr,tmpbuf2,0)) ;
   log(LOG_INFO, "rclose_v3(%d, %d)\n",s, fd) ;
   status = close(fd) ;
   rcode = ( status < 0 ) ? errno : 0 ;


   serrno = 0;
   if( netclose(data_sock) == SOCKET_ERROR )
     log(LOG_DEBUG, "rclose_v3: Error closing data socket fildesc=%d, error=%s\n",
         data_sock, neterror());
   else
      log(LOG_DEBUG, "rclose_v3 : closing data socket fildesc=%d\n", data_sock) ;
   p= rqstbuf;
   marshall_WORD(p, RQST_CLOSE_V3);
   marshall_LONG(p, status);
   marshall_LONG(p, rcode);
#if defined(SACCT)
   rfioacct(RQST_CLOSE_V3,0,0,s,0,0,status,rcode,&myinfo,NULL,NULL);
#endif

   errno = ECONNRESET;
   serrno = 0;
   if (netwrite_timeout(s, rqstbuf, RQSTSIZE, RFIO_CTRL_TIMEOUT) != RQSTSIZE)  {
      log(LOG_ERR, "rclose_v3: netwrite_timeout(): %s\n", neterror());
      return -1 ;
   }
   serrno = 0;
   if( netclose(s) == SOCKET_ERROR )
      log(LOG_DEBUG, "rclose_v3: Error closing control socket fildesc=%d, error=%s\n",
         s, neterror());
   else
      log(LOG_DEBUG, "rclose_v3 : closing ctrl socket fildesc=%d\n", s);

   return status ;
}
