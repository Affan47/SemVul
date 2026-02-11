dsvec_delete_ptr(Dsvec *dsv, void *ptr)
{
  unsigned int ind;

  if (dsv == NULL)
	return(-1);

  for (ind = 0; ind < dsv->nused; ind++) {
	if (dsv->ptr[ind] == ptr)
	  return(dsvec_delete_ptr_index(dsv, ind));
  }

  return(-1);
}
