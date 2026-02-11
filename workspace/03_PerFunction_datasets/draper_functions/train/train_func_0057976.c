node_data_new(int dim, real weight, real *coord, int id){
  node_data nd;
  int i;
  nd = MALLOC(sizeof(struct node_data_struct));
  nd->node_weight = weight;
  nd->coord = MALLOC(sizeof(real)*dim);
  nd->id = id;
  for (i = 0; i < dim; i++) nd->coord[i] = coord[i];
  nd->data = NULL;
  return nd;
}
