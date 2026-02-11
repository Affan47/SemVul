vector_gcd(pk_internal_t* pk,
		numint_t* q, size_t size, numint_t gcd)
{
  size_t i;
  bool not_all_zero;
  numint_t* v = pk->vector_numintp;

  for (i=0;i<size;i++)
    numint_abs(v[i],q[i]);

  do {
    int index=0;
    vector_min_notzero(pk,size,&index,gcd);
    if (numint_sgn(gcd)==0) break;
    not_all_zero = false;
    for (i=0; i<size; i++)
      if ((int)i!=index){
	numint_mod(v[i],v[i],gcd);
	not_all_zero = not_all_zero || numint_sgn(v[i]);
      }
  } while (not_all_zero);
}
