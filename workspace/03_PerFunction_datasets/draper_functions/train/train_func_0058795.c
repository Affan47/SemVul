vector_is_integer(pk_internal_t* pk,
		       numint_t* vec,
		       size_t intdim, size_t realdim)
{
  size_t i;

  for (i=intdim; i<intdim+realdim; i++){
    if (numint_sgn(vec[pk->dec+i]) != 0){
      return false;
    }
  }
  return true;
}
