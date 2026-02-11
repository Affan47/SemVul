ap_dimperm_init(ap_dimperm_t* dimperm, size_t size)
{
  dimperm->dim = size==0 ? NULL : malloc(size*sizeof(ap_dim_t));
  dimperm->size = size;
}
