getfile (int fd,size_t *length)
{
   size_t size = SIZE;
   char *buf;
   ssize_t result;

   if ((buf = mem_alloc (size)) == NULL)
	 {
		log_printf (LOG_ERROR,"failed to allocate memory: %m\n");
		return (NULL);
	 }

   *length = 0;

   while ((result = read (fd,buf + *length,size - *length)) > 0)
	 {
		*length += result;

		if (*length == size)
		  {
			 void *ptr;

			 size += SIZE;

			 if ((ptr = mem_realloc (buf,size)) == NULL)
			   {
				  log_printf (LOG_ERROR,"failed to allocate memory: %m\n");
				  mem_free (buf);
				  return (NULL);
			   }

			 buf = ptr;
		  }
	 }

   if (result < 0)
	 {
		log_printf (LOG_ERROR,"read: %m\n");
		mem_free (buf);
		return (NULL);
	 }

   return (buf);
}
