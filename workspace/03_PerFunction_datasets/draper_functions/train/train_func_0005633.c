mem_realloc_stub (void *ptr,size_t size,const char *file,int line,const char *function)
{
   mem_t *tmp;
   char str[100];
#ifndef REALLOC_BUG_WORKAROUND
   char *area;
#else
   void *ptr2;
#endif
   size_t old_size = size;

   DPRINTF("called %s(%p,%u)\n",__FUNCTION__,ptr,size);

   if (ptr == NULL) return (mem_alloc_stub (size,file,line,function));

   mem_check_stub (file,line,function);

   for (tmp = mem_areas; tmp != NULL && tmp->data != ptr; tmp = tmp->next) ;

   if (tmp == NULL)
	 {
		sprintf (str,"Attempted to realloc unallocated pointer: %p\n",ptr);
		mem_abort2 (str,file,line,function);
	 }

#ifndef REALLOC_BUG_WORKAROUND
   size = (size + 3) & (~3);
   area = xrealloc (file,line,function,tmp->head_sig,size + 2 * sizeof (uint32_t));

   tmp->head_sig = (uint32_t *) area;
   tmp->data = area + sizeof (uint32_t);
   tmp->tail_sig = (uint32_t *) (area + size + sizeof (uint32_t));
   *(tmp->head_sig) = *(tmp->tail_sig) = MEM_SIGNATURE;
   tmp->file = file;
   tmp->line = line;
   tmp->function = function;
   tmp->size = old_size;

   return (tmp->data);
#else
   old_size = old_size > tmp->size ? tmp->size : old_size;

   if ((ptr2 = mem_alloc_stub (size,file,line,function)) == NULL)
	 return (NULL);

   memcpy (ptr2,ptr,old_size);
   mem_free_stub (ptr,file,line,function);
   ptr = ptr2;

   return (ptr2);
#endif
}
