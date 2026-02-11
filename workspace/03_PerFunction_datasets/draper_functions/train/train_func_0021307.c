stop_vsib(ttp_session_t *session)
{
   unsigned long prevb;
   unsigned long b;
   int status;
   int timeout = 0;
   ttp_transfer_t  *xfer  = &session->transfer;
   struct timespec ts;
   ts.tv_sec = 0;
   ts.tv_nsec = 10000000L;

   status = fseeko(xfer->vsib,
                     xfer->file_size, SEEK_SET);

   vsib_ioctl(VSIB_GET_BYTES_IN_BIGBUF, (unsigned long)&b);
   prevb = b;
   while ((b <= prevb) && (timeout++ < 100)) {
      fprintf(stderr, "Waiting for ring buffer to empty (%lu bytes, sl=%d)\n", b, usleeps);


      nanosleep(&ts, NULL);
      usleeps++;
      prevb = b;
      vsib_ioctl(VSIB_GET_BYTES_IN_BIGBUF, (unsigned long)&b);
   }


   vsib_ioctl(VSIB_DELAYED_STOP_DMA, 0);
   {
   unsigned long b;
   timeout = 0;

   vsib_ioctl(VSIB_IS_DMA_DONE, (unsigned long)&b);
   while ((!b) && (timeout++ < 25)) {
     fprintf(stderr, "Waiting for last DMA descriptor (sl=%d)\n",
             usleeps);

     nanosleep(&ts, NULL);

     vsib_ioctl(VSIB_IS_DMA_DONE, (unsigned long)&b);
   }
   }
   vsib_ioctl(VSIB_SET_MODE, VSIB_MODE_STOP);


  if ((shId != -1) && (sh != (ptSh)-1) && (sh != NULL)) {


    if( shmctl(shId, IPC_RMID, NULL) != 0 ) {
       fprintf(stderr, "Shared memory mark remove shmctl() returned non-0\n");
    } else {
       if( shmdt(sh) != 0 ) {
          fprintf(stderr, "Shared memory mark remove shmdt() returned non-0\n");
       }
    }
  }

}
