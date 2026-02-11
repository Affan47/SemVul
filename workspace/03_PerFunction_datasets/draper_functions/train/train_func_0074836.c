ecp_read(int fd, void *buffer, int size, int usec)
{
   int i=0;
   unsigned char *p = (unsigned char *)buffer;

   ecp_fwd_to_rev(fd);

   while (i < size)
   {
      if (ecp_read_data(fd, p+i) != 1)
      {
         usec-=PP_SIGNAL_TIMEOUT;
         if (usec > 0)
            continue;


         return -ETIMEDOUT;
      }
      i++;
   }
   return i;
}
