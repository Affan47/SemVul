get_stress(int m, int dim, int *iw, int *jw, real *w, real *d, real *x, real scaling, void *data, int weighted){
  int i, j;
  real res = 0., dist;

  for (i = 0; i < m; i++){
    for (j = iw[i]; j < iw[i+1]; j++){
      if (i == jw[j]) {
	continue;
      }
      dist = d[j]/w[j];
      if (weighted){
	res += -w[j]*(dist - distance(x, dim, i, jw[j]))*(dist - distance(x, dim, i, jw[j]));
      } else {
	res += (dist - distance(x, dim, i, jw[j]))*(dist - distance(x, dim, i, jw[j]));
      }
    }
  }
  return 0.5*res/scaling/scaling;

}
