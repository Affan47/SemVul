vector_copy(Vector *from, Vector *to) {
  VectorIterator fit, toit;

  if (!to || !from) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "vector_copy: null arguments.\n");
    }
    return;
  }

  if (to->type == SPARSE_ARRAY) {


    vector_zero(to);
  }

  vectorit_set_at_beg(&fit, from);
  vectorit_set_at_beg(&toit, to);
  while (!vectorit_past_end(fit, from) &&
	 vectorit_curr_col(fit, from) < to->dim) {
    if (vectorit_curr_col(toit, to) < vectorit_curr_col(fit, from)) {
      vectorit_zero_elt(&toit, to);
      continue;
    }
    vectorit_insert(&toit, vectorit_curr_col(fit, from),
		    vectorit_curr_val(fit, from), to);
    while (vectorit_curr_col(toit, to) <= vectorit_curr_col(fit, from)) {
      vectorit_next(&toit, to);
    }
    vectorit_next(&fit, from);
  }
  while (!vectorit_past_end(toit, to)) {
    vectorit_zero_elt(&toit, to);
  }
}
