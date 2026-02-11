add_chunk_as(void * chunk, unsigned log_sz)
{
  size_t ofs, limit;
  size_t sz = (size_t)1 << log_sz;

  assert (CHUNK_SIZE >= sz);
  limit = (size_t)CHUNK_SIZE - sz;
  for (ofs = ALIGNMENT - sizeof(AO_t); ofs <= limit; ofs += sz) {
    AO_stack_push(&AO_free_list[log_sz], (AO_t *)((char *)chunk + ofs));
  }
}
