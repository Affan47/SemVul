push_chunk_to_first_free_stack(ChunkAllocator* root, void* p) {
   ChunkAllocator* iter = NULL;

   for (iter = root; iter; iter = iter->next) {
      if (iter->current_chunk < iter->n_chunks) {
         iter->chunks[iter->current_chunk++] = p;
         return;
      }
   }


   assert(0);
}
