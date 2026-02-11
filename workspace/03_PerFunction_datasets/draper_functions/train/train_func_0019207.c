rfio_serrno()
{
   int          s;
   int		last_rferr ;
   int		last_err ;
   int          last_serrno ;
   int 		rt ;

   INIT_TRACE("RFIO_TRACE");
   last_err = errno ;
   last_rferr = rfio_errno ;
   last_serrno = serrno ;
   TRACE(2, "rfio", "rfio_serrno: errno=%d, serrno=%d, rfio_errno=%d",
	 errno, serrno, rfio_errno);
   END_TRACE();
   if (last_serrno != 0) {
     return (serrno);
   } else {
     if (last_rferr != 0) {
       rfio_errno = last_rferr ;
       return (rfio_errno);
     } else {
       if (serrno != 0)  {
         return (serrno);
       } else {
         return (last_err);
       }
     }
   }
}
