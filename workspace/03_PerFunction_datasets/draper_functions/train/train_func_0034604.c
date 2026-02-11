init_heap(void)
{
   if (!exec_heap)
      exec_heap = u_mmInit( 0, EXEC_HEAP_SIZE );

   if (!exec_mem)
      exec_mem = (unsigned char *) mmap(0, EXEC_HEAP_SIZE,
					PROT_EXEC | PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

   return (exec_mem != MAP_FAILED);
}
