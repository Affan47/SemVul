rfio_errmsg_r (s, code, buf, buflen)
int     s;
int     code;
char 	*buf;
size_t 	buflen;
{
   char   *p;
   LONG   len;
   char msg[CA_MAXLINELEN+1];
   char rfio_buf[CA_MAXLINELEN+1];

   if( buf == NULL || buflen <=0 ) return NULL;
   memset(buf, '\0', buflen);

   INIT_TRACE("RFIO_TRACE");
   TRACE(1, "rfio", "rfio_errmsg(%d, %d)",s,code) ;
   p= rfio_buf ;
   marshall_WORD(p, RFIO_MAGIC);
   marshall_WORD(p, RQST_ERRMSG);
   marshall_LONG(p, code);
   TRACE(2,"rfio","rfio_errmsg: sending %d bytes",RQSTSIZE) ;
   if (netwrite_timeout(s,rfio_buf,RQSTSIZE,RFIO_CTRL_TIMEOUT) != RQSTSIZE)  {
      TRACE(2, "rfio" ,"rfio_errmsg: write(): ERROR occured (errno=%d)", errno);
      END_TRACE();
      return((char *) NULL);
   }
   TRACE(2, "rfio", "rfio_errmsg: reading %d bytes", LONGSIZE);
   if (netread_timeout(s,rfio_buf, LONGSIZE, RFIO_CTRL_TIMEOUT) != LONGSIZE) {
      TRACE(2, "rfio" ,"rfio_errmsg: read(): ERROR occured (errno=%d)", errno);
      END_TRACE();
      return((char *) NULL);
   }
   p = rfio_buf ;
   unmarshall_LONG(p, len);
   TRACE(2, "rfio", "rfio_errmsg: reading %d bytes", len);
   if (netread_timeout(s,rfio_buf,len,RFIO_CTRL_TIMEOUT) != len) {
      TRACE(2, "rfio" ,"rfio_errmsg: read(): ERROR occured (errno=%d)", errno);
      END_TRACE();
      return((char *) NULL);
   }
   p= rfio_buf;
   unmarshall_STRINGN(p, msg, CA_MAXLINELEN+1);
   TRACE(1, "rfio", "rfio_errmsg: <%s>", msg);
   END_TRACE();
   strcpy(buf, msg);
   return(buf);
}
