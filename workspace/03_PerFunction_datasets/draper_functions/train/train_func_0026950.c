hash_big_free()
{
   struct h_mem *hmem, *rel;

   for (hmem=mem_block; hmem; ) {
      rel = hmem;
      hmem = hmem->next;
      Dmsg1(100, "free malloc buf=%p\n", rel);
      free(rel);
   }
}
