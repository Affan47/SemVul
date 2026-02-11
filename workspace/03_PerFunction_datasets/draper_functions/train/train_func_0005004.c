free_mem(void *q, unsigned n)
{
  if (n == 0)
    ;
  else {

    void **p = q;
    if (n >= MAX_MEM_LISTS)
      free(p);
    else {

      *p = M[n];
      M[n] = p;
    }
  }
}
