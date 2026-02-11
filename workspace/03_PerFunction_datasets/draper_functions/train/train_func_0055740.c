check_real_array_size(real **a, int len, int *lenmax){
  if (len >= *lenmax){
    *lenmax = len + MAX((int) 0.2*len, 10);
    *a = REALLOC(*a, sizeof(real)*(*lenmax));
  }

}
