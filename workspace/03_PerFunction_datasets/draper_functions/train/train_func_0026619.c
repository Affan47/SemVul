ndmfhh_get_table (struct ndmfhheap *fhh,
  int *fhtype_p, void **table_p, unsigned *n_entry_p)
{
	unsigned		n;

	*fhtype_p = fhh->fhtype;
	*table_p = fhh->heap_top;
	n = (char*)fhh->allo_entry - (char*)fhh->heap_top;
	if (n > 0)
		n /= fhh->entry_size;

	*n_entry_p = n;

	return NDMFHH_RET_OK;
}
