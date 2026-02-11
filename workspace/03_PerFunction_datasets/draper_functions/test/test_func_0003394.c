_mesa_exec_malloc(GLuint size)
{
   struct mem_block *block = NULL;
   void *addr = NULL;

   _glthread_LOCK_MUTEX(exec_mutex);

   if (!init_heap())
      goto bail;

   if (exec_heap) {
      size = (size + 31) & ~31;
      block = mmAllocMem( exec_heap, size, 32, 0 );
   }

   if (block)
      addr = exec_mem + block->ofs;
   else
      printf("_mesa_exec_malloc failed\n");

bail:
   _glthread_UNLOCK_MUTEX(exec_mutex);

   return addr;
}
