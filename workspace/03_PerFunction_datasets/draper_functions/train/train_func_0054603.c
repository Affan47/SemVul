full_write(int fd, const void *buf, size_t count)
{
   ssize_t written = 0;
   while (written < count) {
       ssize_t nwr = write(fd, buf+written, count-written);
       if (nwr < 0) {
           fprintf(stderr, "full_write(): %s\n", strerror(errno));
           return written;
       }
       written += nwr;
   }
   return written;
}
