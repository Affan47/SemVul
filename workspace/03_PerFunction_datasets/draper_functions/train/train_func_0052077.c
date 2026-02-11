vector_bound_itv_linexpr(pk_internal_t* pk,
			      itv_t itv,
			      itv_linexpr_t* linexpr,
			      numint_t* vec, size_t size)
{
  size_t i,dim;
  bool *peq;
  itv_ptr pitv;
  itv_ptr prod;
  numrat_t* rat;

  prod = pk->poly_itv;
  rat = &pk->poly_numrat;

  numrat_set_int(*rat,1);
  itv_set_int(itv,0);
  itv_linexpr_ForeachLinterm(linexpr,i,dim,pitv,peq){
    size_t index = pk->dec + dim;
    if (numint_sgn(vec[index])){
      numint_set(numrat_numref(*rat),vec[index]);
      itv_mul_num(prod,pitv,*rat);
      itv_add(itv,itv,prod);
    }
  }
  if (numint_sgn(vec[polka_cst])){
    numint_set(numrat_numref(*rat),vec[polka_cst]);
    itv_div_num(itv,itv,*rat);
    itv_add(itv,itv,linexpr->cst);
  }
  return;
}
