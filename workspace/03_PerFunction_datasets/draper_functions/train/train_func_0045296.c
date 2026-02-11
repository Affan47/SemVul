csbe_malloc(size)
unsigned size;
{
  char *p;
  if ((p = (char *)malloc(size)) == NULL) {
    fprintf(stderr, "malloc: Memory Exausted.\n");
    exit(3);
  }
  return p;
}
