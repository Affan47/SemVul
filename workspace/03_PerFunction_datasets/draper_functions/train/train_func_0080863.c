QuadTree_get_supernodes(QuadTree qt, real bh, real *point, int nodeid, int *nsuper,
			     int *nsupermax, real **center, real **supernode_wgts, real **distances, double *counts, int *flag){
  int dim = qt->dim;

  (*counts) = 0;

  *nsuper = 0;

  *flag = 0;
  *nsupermax = 10;
  if (!*center) *center = MALLOC(sizeof(real)*(*nsupermax)*dim);
  if (!*supernode_wgts) *supernode_wgts = MALLOC(sizeof(real)*(*nsupermax));
  if (!*distances) *distances = MALLOC(sizeof(real)*(*nsupermax));
  QuadTree_get_supernodes_internal(qt, bh, point, nodeid, nsuper, nsupermax, center, supernode_wgts, distances, counts, flag);

}
