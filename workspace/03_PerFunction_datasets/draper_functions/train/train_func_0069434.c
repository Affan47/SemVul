vm_chunk_create(vm_instance_t *vm)
{
   vm_chunk_t *chunk;
   size_t area_len;

   if (!(chunk = malloc(sizeof(*chunk))))
      return NULL;

   area_len = VM_CHUNK_AREA_SIZE * VM_PAGE_SIZE;

   if (!(chunk->area = m_memalign(VM_PAGE_SIZE,area_len))) {
      free(chunk);
      return NULL;
   }

   chunk->page_alloc = 0;
   chunk->page_total = VM_CHUNK_AREA_SIZE;

   chunk->next = vm->chunks;
   vm->chunks = chunk;
   return chunk;
}
