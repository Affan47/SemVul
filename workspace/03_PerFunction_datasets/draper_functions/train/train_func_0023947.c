dsvec_shift(Dsvec *dsv, int count)
{
  unsigned int i;
  size_t len;

  if (count == 0)
	return(0);

  len = dsvec_len(dsv);
  if (count < 0 || count > len)
	return(-1);

  for (i = 0; i < len - count; i++)
	dsv->ptr[i] = dsv->ptr[i + count];

  while (i < len)
	dsv->ptr[i++] = NULL;

  dsv->nused -= count;

  return(0);
}
