_eio_file_write(int fd, void *mem, ssize_t length)
{
   ssize_t count;

   if (length == 0) return EINA_TRUE;

   count = write(fd, mem, length);
   if (count != length) return EINA_FALSE;
   return EINA_TRUE;
}
