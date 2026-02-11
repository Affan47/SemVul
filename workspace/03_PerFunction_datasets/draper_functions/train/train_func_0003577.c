copy_ntuple(ntuple_list src, ntuple_list des)
{

  if( src == NULL ) error("copy_ntuple: invalid n-tuple input.");
  if( des == NULL ) error("copy_ntuple: invalid n-tuple input.");
  if( src->dim != des->dim ) error("copy_ntuple: different dimension of input.");

  int i, j, nb, dim;
  nb = src->size;
  dim = src->dim;

  des->size = 0;

  for(i = 0; i < nb; i++) {
    if(des->size == des->max_size)
      enlarge_ntuple_list(des);
    for(j = 0; j < dim; j++)
      des->values[i*dim+j] = src->values[i*dim+j];
    des->size++;
  }
}
