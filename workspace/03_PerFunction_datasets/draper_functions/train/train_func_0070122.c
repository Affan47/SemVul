get_boundingbox(int n, int dim, real *x, real *width, real *bbox){
  int i;
  bbox[0] = bbox[1] = x[0];
  bbox[2] = bbox[3] = x[1];

  for (i = 0; i < n; i++){
    bbox[0] = MIN(bbox[0], x[i*dim] - width[i*dim]);
    bbox[1] = MAX(bbox[1], x[i*dim] + width[i*dim]);
    bbox[2] = MIN(bbox[2], x[i*dim + 1] - width[i*dim+1]);
    bbox[3] = MAX(bbox[3], x[i*dim + 1] + width[i*dim+1]);
  }
}
