setmtime(const FileTimestamp &ts)
{
   getfd();


   struct stat st;
   if(fstat(fd,&st)!=-1 && labs(st.st_mtime-ts)<=ts.ts_prec)
      return;

   struct utimbuf ut;
   ut.actime=ut.modtime=ts;
   utime(full_name,&ut);
}
