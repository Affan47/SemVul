cdk_subpkt_find_nth (cdk_subpkt_t ctx, size_t type, size_t idx)
{
  cdk_subpkt_t s;
  size_t pos;

  pos = 0;
  for (s = ctx; s; s = s->next)
    {
      if (s->type == type && pos++ == idx)
        return s;
    }

  return NULL;
}
