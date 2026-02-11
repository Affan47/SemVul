comparefastakeys(const void *a,const void *b)
{
  int cmp = strcmp(((Fastakeyquery *) a)->fastakey,
                   ((Fastakeyquery *) b)->fastakey);

  if (cmp < 0)
  {
    return -1;
  }
  if (cmp > 0)
  {
    return 1;
  }
  if (((Fastakeyquery *) a)->frompos < ((Fastakeyquery *) b)->frompos)
  {
    return -1;
  }
  if (((Fastakeyquery *) a)->frompos > ((Fastakeyquery *) b)->frompos)
  {
    return 1;
  }
  if (((Fastakeyquery *) a)->topos < ((Fastakeyquery *) b)->topos)
  {
    return -1;
  }
  if (((Fastakeyquery *) a)->topos > ((Fastakeyquery *) b)->topos)
  {
    return 1;
  }
  return 0;
}
