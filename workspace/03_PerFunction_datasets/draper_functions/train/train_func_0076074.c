huft_free(
  struct InflateState *is,
  struct huft *t
)
{
  struct huft *p, *q;


  p = t;
  while (p != (struct huft *)NULL)
  {
    q = (--p)->v.t;
    (*is->free_ptr)((char*)p);
    p = q;
  }
  return 0;
}
