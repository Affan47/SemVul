Seek(uint64_t sector) {
   int retval = 1;
   off_t seekTo, sought;


   if (!isOpen) {
      retval = OpenForRead();
   }

   if (isOpen) {
      seekTo = sector * (uint64_t) GetBlockSize();
      sought = lseek64(fd, seekTo, SEEK_SET);
      if (sought != seekTo) {
         retval = 0;
      }
   }
   return retval;
}
