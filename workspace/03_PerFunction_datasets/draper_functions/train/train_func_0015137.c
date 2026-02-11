vector_is_null_strict(pk_internal_t* pk,
			   numint_t* q, size_t size)
{
  size_t i;
  bool res = true;

  if (size>polka_cst){
    res = numint_sgn(q[polka_cst])==0;
    if (res){
      for (i=pk->dec; i<size; i++){
	if (numint_sgn(q[i])!=0){
	  res = false;
	  break;
	}
      }
    }
  }
  return res;
}
