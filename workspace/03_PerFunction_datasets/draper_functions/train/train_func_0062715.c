plot_dot_edges(FILE *f, SparseMatrix A, int dim, real *x){
  int i, *ia, *ja, j;


  int n = A->m;
  ia = A->ia;
  ja = A->ja;
  for (i = 0; i < n; i++){
    for (j = ia[i]; j < ia[i+1]; j++){
      if (ja[j] == i) continue;
      fprintf(f,"%d -- %d;\n",i,ja[j]);
    }
  }
}
