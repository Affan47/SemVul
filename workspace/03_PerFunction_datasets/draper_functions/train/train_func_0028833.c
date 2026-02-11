dsvec_ptr_rindex(Dsvec *dsv, unsigned int rind)
{
  int offset;

  offset = dsv->nused - rind - 1;
  if (offset < 0)
	return(NULL);
  return(dsv->ptr[offset]);
}
