md_first_free(void *base) {
  lmc_mem_descriptor_t *md = base;
  return md->first_free == 0 ? 0 : base + md->first_free;
}
