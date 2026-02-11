rfio_serror_r(buf, buflen)
char *buf;
size_t buflen;
{
   int          s;
   int		last_rferr ;
   int		last_err ;
   int          last_serrno ;
   int 		rt ;
   char 	*rferrmsg ;
   char 	rerrlist[CA_MAXLINELEN+1] ;

   if( buf == NULL || buflen <=0 ) return NULL;
   memset(buf, '\0', buflen);

   INIT_TRACE("RFIO_TRACE");
   last_err = errno ;
   last_rferr = rfio_errno ;
   last_serrno = serrno ;
   TRACE(2, "rfio", "rfio_serror: errno=%d, serrno=%d, rfio_errno=%d",
	 errno, serrno, rfio_errno);
   END_TRACE();
   if (last_serrno != 0) {
      return ( sstrerror(serrno) );
   }
   else    {
      if (last_rferr != 0)        {
	 if (last_rferr >= SEBASEOFF)
	    return ( sstrerror(last_rferr) );
	 if ((s=rfio_connect(rfio_lasthost(),&rt)) == -1)  {
	    sprintf(rerrlist,"Unable to fetch remote error %d",last_rferr);
	    rfio_errno = last_rferr ;
	    strcpy(buf, rerrlist);
	    return (buf);
	 }
	 else    {
	    if ( (rferrmsg = rfio_errmsg(s,last_rferr)) != NULL )
	       sprintf(rerrlist, "%s (error %d on %s)", rferrmsg, last_rferr, rfio_lasthost());
	    else
	       sprintf(rerrlist, " (error %d on %s)", last_rferr, rfio_lasthost());
	    netclose(s);
	    rfio_errno = last_rferr ;
	    strcpy(buf, rerrlist);
	    return (buf);
	 }
      }
      else    {
	 if (serrno != 0)  {
	    strcpy( buf, sstrerror(serrno));
	    return (buf);
	 }
	 else {
	    strcpy(buf, strerror(last_err));
	    return (buf);
	 }
      }
   }
}
