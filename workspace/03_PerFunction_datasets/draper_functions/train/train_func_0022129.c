expanding_array_set(ExpandingType d, int c, ExpandingArray *A) {

  int newsize, offset, mid, i;

  if (!A) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "expanding_array_set: null array.\n");
    }
    return;
  }

  if (A->first_elt == 0 && c == A->n_elts) {


    expanding_array_insert(d, A);
    return;
  }

  if (c+A->first_elt >= A->length || c+A->first_elt < 0) {
    if (fabs(c+A->first_elt) < 2*A->length) {
      if (A->length == 0) {
	A->length = 1;
      }
      newsize = 2*A->length;
    } else {
      newsize = (fabs(c+A->first_elt)+1);
    }
    expand(A, newsize);
    if (!(A->length)) {
      if (MATR_DEBUG_MODE) {
	fprintf
	  (stderr,
	   "expanding_array_insert: unable to expand array enough to do insert.\n");
      }
      return;
    }


    mid = A->n_elts/2;
    offset = A->length/2 - mid;
    for (i = A->last_elt; i >= A->first_elt; i--) {
      if (A->compact) {
	A->data.compact[i-A->first_elt+offset] = A->data.compact[i];
      } else {
	A->data.precise[i-A->first_elt+offset] = A->data.precise[i];
      }
    }
    A->last_elt += offset-A->first_elt;
    A->first_elt = offset;
  }

  if (A->compact) {
    A->data.compact[A->first_elt+c] = *(d.compact);
  } else {
    A->data.precise[A->first_elt+c] = *(d.precise);
  }
  if (c+A->first_elt > A->last_elt) {
    A->last_elt = c + A->first_elt;
    A->n_elts++;
  }

  if (c+A->first_elt < A->first_elt) {
    A->first_elt += c;
    A->n_elts++;
  }
}
