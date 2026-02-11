expanding_array_map(void **addr, void *last_addr) {
  ExpandingArray *A;

  if (!addr || !*addr || !last_addr || *addr >= last_addr) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "expanding_array_map: null arguments.\n");
    }
    return NULL;
  }

  if (*addr + sizeof(ExpandingArray) > last_addr) {

    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "expanding_array_map: not enough memory for array.\n");
    }
    return NULL;
  }

  A = (ExpandingArray *)(*addr);
  *addr += sizeof(ExpandingArray);
  A->length = A->n_elts;
  A->last_elt = A->n_elts-1;
  A->first_elt = 0;
  A->was_mapped = 1;

  if (A->length >= A->n_elts && A->first_elt < A->length && A->first_elt >= 0
      && ((A->compact &&
	   *addr + A->n_elts*sizeof(CompactExpandingType) <= last_addr) ||
	  (!(A->compact) &&
	   *addr + A->n_elts*sizeof(PreciseExpandingType) <= last_addr))) {
    if (A->compact) {
      A->data.compact = (CompactExpandingType *)(*addr);
      *addr += A->n_elts*sizeof(CompactExpandingType);
    } else {
      A->data.precise = (PreciseExpandingType *)(*addr);
      *addr += A->n_elts*sizeof(PreciseExpandingType);
    }
  } else {
    if (MATR_DEBUG_MODE && A->n_elts) {
      fprintf(stderr, "expanding_array_map: array cannot contain all of its elements. This is likely a corrupted file.\n");
    }
    A->length = 0;
    A->n_elts = 0;
    A->first_elt = 0;
    A->last_elt = -1;
    A->data.precise = NULL;
  }

  return A;
}
