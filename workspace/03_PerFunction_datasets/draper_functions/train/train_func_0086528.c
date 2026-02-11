xrealloc (const char *file,int line,const char *function,void *ptr,size_t size)
{
   void *ptr2;

   if ((ptr2 = realloc (ptr,size)) == NULL)
	 fail_stub ("realloc(ptr: %p, size: %u): %m\n"
				"Attempted allocation in file \"%s\" at line %d in function %s()\n",
				ptr,size,
				file,line,function);

   return (ptr2);
}
