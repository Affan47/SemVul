QuadTree_get_quadrant(int dim, real *center, real *coord){


  int d = 0, i;

  for (i = dim - 1; i >= 0; i--){
    if (coord[i] - center[i] < 0){
      d = 2*d;
    } else {
      d = 2*d+1;
    }
  }
  return d;
}
