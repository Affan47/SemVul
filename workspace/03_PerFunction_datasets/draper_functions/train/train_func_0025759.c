Multilevel_init(SparseMatrix A, SparseMatrix D, real *node_weights){
  Multilevel grid;
  if (!A) return NULL;
  assert(A->m == A->n);
  grid = GNEW(struct Multilevel_struct);
  grid->level = 0;
  grid->n = A->n;
  grid->A = A;
  grid->D = D;
  grid->P = NULL;
  grid->R = NULL;
  grid->node_weights = node_weights;
  grid->next = NULL;
  grid->prev = NULL;
  grid->delete_top_level_A = FALSE;
  return grid;
}
