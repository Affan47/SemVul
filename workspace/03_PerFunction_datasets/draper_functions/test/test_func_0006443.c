ndmfhh_prepare (struct ndmfhheap *fhh,
  int fhtype, int entry_size,
  unsigned n_item, unsigned total_size_of_items)
{
	void *			pe;
	void *			pi;
	unsigned		items_need;

	if (fhh->heap_base == 0)
		return NDMFHH_RET_NO_HEAP;

	if (fhh->allo_entry == fhh->heap_top) {
		fhh->fhtype = fhtype;
		fhh->entry_size = entry_size;
	} else {
		if (fhh->fhtype != fhtype)
			return NDMFHH_RET_TYPE_CHANGE;

		if (fhh->entry_size != entry_size)
			return NDMFHH_RET_ENTRY_SIZE_MISMATCH;
	}

	items_need = total_size_of_items + n_item * NDMOS_CONST_ALIGN + SLOP;

	pe = (char*)fhh->allo_entry + fhh->entry_size;
	pi = (char*)fhh->allo_item - items_need;

	if (pe >= pi)
		return NDMFHH_RET_OVERFLOW;


	return NDMFHH_RET_OK;
}
