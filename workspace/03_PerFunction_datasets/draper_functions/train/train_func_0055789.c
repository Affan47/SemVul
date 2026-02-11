FREE(void *ptr)
{
   if (NULL == ptr) fatal("Attempt to free NULL pointer\n");
   else free(ptr);

   malloc_count--;
   return;
}
