vbprintf (const char *fmt,va_list ap)
{

   int n,size = 100;
   char *buf,*ptr;
   va_list ap_copy;

   if (fmt == NULL) return (NULL);

   if (*fmt == '\0')
	 {
		if ((buf = mem_alloc (sizeof (char))) == NULL)
		  return (NULL);
		*buf = '\0';
		return (buf);
	 }

   if ((buf = mem_alloc (size * sizeof (char))) == NULL)
	 return (NULL);

   for (;;)
	 {

		va_copy (ap_copy,ap);
		n = vsnprintf (buf,size,fmt,ap_copy);
		va_end (ap_copy);


		if (n > -1 && n < size) break;


		if (n > -1)
		  size = n + 1;
		else
		  size *= 2;

		if ((ptr = mem_realloc (buf,size * sizeof (char))) == NULL)
		  {
			 int saved = errno;
			 mem_free (buf);
			 errno = saved;
			 return (NULL);
		  }
		else buf = ptr;
	 }

   return (buf);
}
