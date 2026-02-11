vector_add_col_ns(Vector *v) {
  NSData tmpdata;

  if (!v) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "vector_add_col: null vector.\n");
    }
    return;
  }

  if (v->compact) {
    if (!(v->was_mapped) ||
	(v->was_mapped &&
	 (void *)v + sizeof(Vector) != (void *)(v->data.nsarray.compact))) {
      v->data.nsarray.compact = (int *)realloc(v->data.nsarray.compact,
					       sizeof(int)*(v->dim+1));
    } else {
      tmpdata.compact = v->data.nsarray.compact;
      v->data.nsarray.compact = (int *)malloc(sizeof(int)*(v->dim+1));
      if (v->data.nsarray.compact) {
	memcpy(v->data.nsarray.compact, tmpdata.compact, sizeof(int)*v->dim);
      }
    }
    if (!v->data.nsarray.compact) {
      if (MATR_DEBUG_MODE) {
	fprintf(stderr, "Error adding a column to non-sparse vector.\n");
      }
      v->dim = 0;
      v->nz = 0;
      return;
    }
  } else {
    if (!(v->was_mapped) ||
	(v->was_mapped &&
	 (void *)v + sizeof(Vector) != (void *)(v->data.nsarray.precise))) {
      v->data.nsarray.precise = (double *)realloc(v->data.nsarray.precise,
						  sizeof(double)*(v->dim+1));
    } else {
      tmpdata.precise = v->data.nsarray.precise;
      v->data.nsarray.precise = (double *)malloc(sizeof(double)*(v->dim+1));
      if (v->data.nsarray.precise) {
	memcpy(v->data.nsarray.precise, tmpdata.precise, sizeof(double)*v->dim);
      }
    }
    if (!v->data.nsarray.precise) {
      if (MATR_DEBUG_MODE) {
	fprintf(stderr, "Error adding a column to non-sparse vector.\n");
      }
      v->dim = 0;
      v->nz = 0;
      return;
    }
  }
  v->dim++;
  vector_set(v, v->dim-1, 0);
}
