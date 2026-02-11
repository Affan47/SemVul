rfio_fileno(fp)
RFILE *fp;
{
   int     fd;


   INIT_TRACE("RFIO_TRACE");
   TRACE(1, "rfio", "rfio_fileno(%x)", fp);

   if ( fp == NULL ) {
      errno = EBADF;
      END_TRACE();
      return -1 ;
   }


   if (rfio_rfilefdt_findptr(fp,FINDRFILE_WITH_SCAN) == -1)
      fd = fileno((FILE *)fp);
   else
      fd = fp->s;
   END_TRACE() ;
   return (fd) ;
}
