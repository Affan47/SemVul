read(const char *map) {
  int nsize = 0;
  memcpy(&nsize, map, sizeof(nsize));
  if(nsize <= 0 || nsize > 64)
    eraise(MismatchingSize) << "Invalid matrix size '" << nsize << "'. Must be between 1 and 64";

  size = nsize;
  alloc_columns();
  memcpy(columns, map + sizeof(size), sizeof(uint64_t) * size);
  return sizeof(size) + sizeof(uint64_t) * size;
}
