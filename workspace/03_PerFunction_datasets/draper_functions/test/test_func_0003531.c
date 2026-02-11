vector_normalize_expr(pk_internal_t* pk,
			   numint_t* q, size_t size)
{
  size_t i;

  assert(size<=pk->maxcols);


  vector_gcd(pk,&q[0],size, pk->vector_tmp[1]);

  if (numint_cmp_int(pk->vector_tmp[1],1)>0){
    for (i=0; i<size; i++)
      numint_divexact(q[i],q[i],pk->vector_tmp[1]);
    return true;
  }
  else
    return false;
}
