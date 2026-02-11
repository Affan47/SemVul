plot_edges(int n, int dim, real *x, SparseMatrix A){
  int i, j, k;
  int *ia, *ja;

  if (!A) {
    printf("Graphics[{}]");
    return;
  }
  ia = A->ia; ja = A->ja;

  printf("Graphics[(* edges of the graph*){");
  for (i = 0; i < n; i++){
    for (j = ia[i]; j < ia[i+1]; j++){
      if (i > 0 && j == ia[i]) printf(",");;
      printf("Line[{{");
      for (k = 0; k < 2; k++) {
	printf("%f",x[i*dim+k]);
	if (k == 0) printf(",");
      }
      printf("},{");
      for (k = 0; k < 2; k++) {
	printf("%f",x[ja[j]*dim+k]);
	if (k == 0) printf(",");
      }
      printf("}}]");
      if (j < ia[i+1] - 1) printf(",");
    }
  }
  printf("}(* end of edges of the graph*)]");

}
