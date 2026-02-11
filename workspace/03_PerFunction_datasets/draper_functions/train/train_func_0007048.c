Compoundpos_heap_init (Compoundpos_T compoundpos, int querylength, int diagterm) {
  Batch_T batch;
  int startbound, i;

  compoundpos->heapsize = 0;
  for (i = 0; i < compoundpos->n; i++) {
    batch = &(compoundpos->batchpool[i]);
    batch->positionptr = compoundpos->positions[i];
    batch->nentries = compoundpos->npositions[i];
    if (diagterm < querylength) {
      startbound = querylength - diagterm;
#ifdef WORDS_BIGENDIAN
      while (batch->nentries > 0 && Bigendian_convert_uint(*batch->positionptr) < (unsigned int) startbound) {
	debug11(printf("Eliminating diagonal %u as straddling beginning of genome (Compoundpos_heap_init)\n",
		       Bigendian_convert_uint(*batch->positionptr)));
	++batch->positionptr;
	--batch->nentries;
      }
#else
      while (batch->nentries > 0 && *batch->positionptr < (unsigned int) startbound) {
	debug11(printf("Eliminating diagonal %u as straddling beginning of genome (Compoundpos_heap_init)\n",
		       *batch->positionptr));
	++batch->positionptr;
	--batch->nentries;
      }
#endif
    }
    if (batch->nentries > 0) {
#ifdef WORDS_BIGENDIAN
      batch->position = Bigendian_convert_uint(*batch->positionptr);
#else
      batch->position = *batch->positionptr;
#endif
      heap_insert_even(compoundpos->heap,&compoundpos->heapsize,batch,batch->position);
    }
  }

  compoundpos->sentinel_struct.position = (Genomicpos_T) -1U;
  compoundpos->sentinel_struct.positionptr = &(compoundpos->sentinel_struct.position);
  compoundpos->sentinel = &compoundpos->sentinel_struct;

  for (i = compoundpos->heapsize+1; i <= compoundpos->n; i++) {
    compoundpos->heap[i] = compoundpos->sentinel;
  }

  return;
}
