consume64_thread(int *ptr)
{
   int      fd = *ptr;
   int      byte_written = -1;
   int      error = 0, end = 0;
   off64_t  total_consumed = 0;
   char     *buffer_to_write;
   int      len_to_write;
   int      saved_errno;
   char     tmpbuf[21];

   while ((! error) && (! end)) {
      log(LOG_DEBUG, "consume64_thread: calling Csemaphore_down(&full64)\n");
      Csemaphore_down(&full64);

      buffer_to_write = array[consumed64 % daemonv3_wrmt_nbuf].p;
      len_to_write    = array[consumed64 % daemonv3_wrmt_nbuf].len;

      if (len_to_write > 0) {
         log(LOG_DEBUG,"consume64_thread: Trying to write %d bytes from %X\n",
            len_to_write, buffer_to_write);

         byte_written = write(fd, buffer_to_write, len_to_write);
         saved_errno = errno;
         log(LOG_DEBUG, "consume64_thread: succeeded to write %d bytes\n", byte_written);


         if ((byte_written >= 0) && (byte_written != len_to_write)) {
            byte_written = -1;
            saved_errno = errno = ENOSPC;
         }


         if (byte_written == -1)   {
            error = 1;
            if (Cthread_mutex_lock(&write_error)) {
               log(LOG_ERR,"consume64_thread: Cannot get mutex : serrno=%d\n", serrno);
               return(NULL);
            }

            write_error = saved_errno;

            if (Cthread_mutex_unlock(&write_error)) {
               log(LOG_ERR,"consume64_thread: Cannot release mutex : serrno=%d\n", serrno);
               return(NULL);
            }

            log(LOG_DEBUG,"consume64_thread: Error when writing : buffers=%d, error=%d\n",
               consumed64,saved_errno);
         }
         else {

            total_consumed += byte_written;
            log(LOG_DEBUG,"consume64_thread: Has written buf %d to disk (len %d)\n",
               consumed64 % daemonv3_wrmt_nbuf, byte_written);
         }
      }
      else {
         if (len_to_write == 0) {
            log(LOG_DEBUG,"consume64_thread: End of writing : total consumed = %s, buffers=%d\n",
               u64tostr(total_consumed,tmpbuf,0), consumed64);
            end = 1;
         }
         else {

            log(LOG_DEBUG,"consume64_thread: Error on reading : total consumed = %s, buffers=%d\n",
               u64tostr(total_consumed,tmpbuf,0), consumed64);
            error = 1;
         }
      }

      consumed64++;
      log(LOG_DEBUG, "consume64_thread: calling Csemaphore_up(&empty64)\n");
      Csemaphore_up(&empty64);
   }
   return(NULL);
}
