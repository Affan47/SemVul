Operator_uniform_stress_diag_precon_new(SparseMatrix A, real alpha){
  Operator o;
  real *diag;
  int i, j, m = A->m, *ia = A->ia, *ja = A->ja;
  real *a = (real*) A->a;

  assert(A->type == MATRIX_TYPE_REAL);

  assert(a);

  o = MALLOC(sizeof(struct Operator_struct));
  o->data = MALLOC(sizeof(real)*(m + 1));
  diag = (real*) o->data;

  diag[0] = m;
  diag++;
  for (i = 0; i < m; i++){
    diag[i] = 1./(m-1);
    for (j = ia[i]; j < ia[i+1]; j++){
      if (i == ja[j] && ABS(a[j]) > 0) diag[i] = 1./((m-1)*alpha+a[j]);
    }
  }

  o->Operator_apply = Operator_diag_precon_apply;

  return o;
}
