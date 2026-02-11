alloc_client_register(i32 n)
{
  client_register_t *r = xmalloc(sizeof(client_register_t));
  r->n = n;
  r->c = xmalloc(n * sizeof(client_t));
  i32 i;
  for(i = 0; i < r->n; i++) {
    r->c[i].in_use = 0;
    r->c[i].mask = 0;
  }
  return r;
}
