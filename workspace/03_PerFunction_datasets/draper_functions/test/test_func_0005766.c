vectorit_zero_elt(VectorIterator *vit, Vector *v) {
  VectorIterator tmpit;
  unsigned int currcol = vectorit_curr_col(*vit, v);

  if (!v || !vit) {
    if (MATR_DEBUG_MODE) {
      fprintf(stderr, "vectorit_zero_elt: null arguments.\n");
    }
    if (vit) {
      vit->nscurr = -1;
    }
    return;
  }

  vectorit_copy(*vit, &tmpit);
  vectorit_next(&tmpit, v);
  vectorit_set(*vit, 0, v);


  vectorit_copy(tmpit, vit);
  vectorit_prev(&tmpit, v);
  if ((!vectorit_past_beg(tmpit, v) &&
       vectorit_curr_col(tmpit, v) > currcol)) {
    vectorit_copy(tmpit, vit);
  }
}
