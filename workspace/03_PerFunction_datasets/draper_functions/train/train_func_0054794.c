pk_internal_realloc_lazy(pk_internal_t* pk, size_t maxdims)
{
  if (maxdims > pk->maxdims){
    pk_internal_clear(pk);
    pk_internal_init(pk,maxdims);
  }
}
