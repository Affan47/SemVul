hash_info(Hashtab h)
{
  int i;
  printf("\nHash info, size=%d\n", h->size);
  for (i = 0; i < h->size; i++) {
    Hashnode p;
    int n = 0;
    for (p = h->table[i]; p; p = p->next)
      n++;
    if (n > 0)
      printf("    bucket %d has %d objects\n", i, n);
  }
  fflush(stdout);
}
