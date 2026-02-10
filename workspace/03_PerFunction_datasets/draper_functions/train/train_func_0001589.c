dsvec_strneq(Dsvec *dsv1, Dsvec *dsv2, size_t len)
{
  unsigned int i;

  if (dsvec_len(dsv1) < len || dsvec_len(dsv2) < len)
	return(0);

  for (i = 0; i < len; i++) {
	char *p, *q;

	p = (char *) dsvec_ptr_index(dsv1, i);
	q = (char *) dsvec_ptr_index(dsv2, i);
	if (!streq(p, q))
	  return(0);
  }

  return(1);
}
