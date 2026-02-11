attrs_list_copy (attrs *dstp, attrs src)
{
  attrs n;

  attrs_list_clear (dstp);
  for (; src; src = src->next)
    {
      n = (attrs) pool_alloc (attrs_pool);
      n->loc = src->loc;
      n->dv = src->dv;
      n->offset = src->offset;
      n->next = *dstp;
      *dstp = n;
    }
}
