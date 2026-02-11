SparseMatrix_has_diagonal(SparseMatrix A){

  int i, j, m = A->m, *ia = A->ia, *ja = A->ja;

  for (i = 0; i < m; i++){
    for (j = ia[i]; j < ia[i+1]; j++){
      if (i == ja[j]) return TRUE;
    }
  }
  return FALSE;
}
