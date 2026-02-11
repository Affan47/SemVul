rs_are_different_vectors(const int *vect1,
					   const int *vect2,
					   const int dim) {
  int i;
  for(i=0; i<dim; i++) {
    if(vect1[i] != vect2[i]) {
      printf("### ERROR: rs_are_different_vectors(): vect1[%d]: %d vect2[%d]: %d\n", i, vect1[i], i, vect2[i]);
      return(0);
    }
  }
  return(1);
}
