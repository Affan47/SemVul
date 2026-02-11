lmc_compact_free_chunks(void *base, size_t va_chunk) {
  lmc_mem_descriptor_t *md = base;
  lmc_mem_chunk_descriptor_t *chunk = base + va_chunk;
  size_t c_size = chunk->size;
  size_t va_chunk_p = 0;
  size_t va_c_free_chunk = 0;
  lmc_mem_chunk_descriptor_t* c_free_chunk = base + va_c_free_chunk;
  size_t va_previous = 0;
  size_t merge1_chunk = 0;
  int merge1 = 0;
  while (c_free_chunk) {
    va_c_free_chunk = (void *)c_free_chunk - base;
    if (va_c_free_chunk != va_chunk) {
      if (c_free_chunk->next == va_chunk) { va_chunk_p = va_c_free_chunk; }
      else if (!merge1) {


        if (va_c_free_chunk + c_free_chunk->size == va_chunk) {
          merge1 = 1;
          merge1_chunk = va_c_free_chunk;
        } else


        if (va_chunk + c_size == va_c_free_chunk) {
          chunk->size += c_free_chunk->size;
          LMC_TEST_CRASH
          if (chunk->next == va_c_free_chunk) { va_previous = va_chunk; }
          LMC_TEST_CRASH
          lmc_mem_chunk_descriptor_t *p = va_previous ? base + va_previous : 0;
          LMC_TEST_CRASH
          if (p) { p->next = c_free_chunk->next; }
          LMC_TEST_CRASH
          break;
        }
      }
      va_previous = va_c_free_chunk;
    }
    va_c_free_chunk = c_free_chunk->next;
    if (va_c_free_chunk == 0) { c_free_chunk = NULL; }
    else { c_free_chunk = base + va_c_free_chunk; }
  }


  if (merge1) {
    lmc_mem_chunk_descriptor_t *cd = base + merge1_chunk;
    lmc_mem_chunk_descriptor_t *p = va_chunk_p ? base + va_chunk_p : 0;
    lmc_mem_chunk_descriptor_t *vacd = va_chunk? base + va_chunk : 0;
    LMC_TEST_CRASH
    if (p) { p->next = vacd->next; }
    LMC_TEST_CRASH
    if (md->first_free == va_chunk) { md->first_free = chunk->next; }
    LMC_TEST_CRASH
    cd->size += c_size;
  }
}
