initCache() {
  cachetail = 1;
  cache = malloc(CACHESIZE);
  if(!cache) {
    printf("Failure to allocate cache of size %lld\n", CACHESIZE);
    exit(1);
  }
  cachemap = calloc(CACHEMAPSIZE, sizeof(unsigned long long));
  if(!cachemap) {
    printf("Failure to allocate cachemap of size %d * %lu\n", CACHEMAPSIZE, sizeof(unsigned long long));
    exit(1);
  }
}
