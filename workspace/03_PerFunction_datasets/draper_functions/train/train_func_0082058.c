source_zip_read(source_file_t *filep, void *buf, size_t size) {
   int result;

   if (filep != NULL) {
       result = archive_read_data(filep->zip, buf, size);
   }
   else {
       result = -1;
       errno  = EBADF;
   }

   return result;
}
