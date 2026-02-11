Indexdb_merge_compoundpos (int *nmerged, Compoundpos_T compoundpos, int diagterm) {
  int i;
  Batch_T batch;
  struct Batch_T batchpool[16];
  int nentries = 0;

  debug(printf("merge_compoundpos, sizes:"));

  for (i = 0; i < compoundpos->n; i++) {
    batch = &(batchpool[i]);
    batch->positionptr = compoundpos->positions[i];
    batch->nentries = compoundpos->npositions[i];
    debug(printf(" %d",batch->nentries));
    nentries += batch->nentries;
  }
  debug(printf("\n"));

  if (nentries == 0) {
    *nmerged = 0;
    return (Genomicpos_T *) NULL;
  } else if (compoundpos->n == 4) {
    return merge_batches_one_heap_4_existing(&(*nmerged),batchpool,nentries,diagterm);
  } else {
    return merge_batches_one_heap_16_existing(&(*nmerged),batchpool,nentries,diagterm);
  }
}
