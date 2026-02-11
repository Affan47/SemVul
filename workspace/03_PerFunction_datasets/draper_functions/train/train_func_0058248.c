box_set_top(box_t* a)
{
  size_t i;
  size_t nbdims;

  nbdims = a->intdim + a->realdim;
  if (a->p==NULL){
    box_init(a);
  };
  for (i=0; i<nbdims; i++){
    itv_set_top(a->p[i]);
  }
}
