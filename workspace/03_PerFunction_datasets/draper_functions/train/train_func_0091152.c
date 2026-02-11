vector_set_ap_generator0(pk_internal_t* pk,
			      numint_t* vec,
			      ap_generator0_t* gen,
			      size_t intdim, size_t realdim)
{
  assert(gen->gentyp != AP_GEN_VERTEX);
  itv_linexpr_set_ap_linexpr0(pk->itv,
			      &pk->poly_itv_linexpr,
			      gen->linexpr0);
  vector_set_itv_linexpr(pk, vec, &pk->poly_itv_linexpr, intdim+realdim, +1);

  if (pk->strict)
    numint_set_int(vec[polka_eps],0);

  numint_set_int(vec[0],
		 ( ((gen->gentyp == AP_GEN_LINE) || (gen->gentyp == AP_GEN_LINEMOD)) ?
		   0 :
		   1 ));
  if (gen->gentyp != AP_GEN_VERTEX){
    numint_set_int(vec[polka_cst],0);
    vector_normalize(pk,vec, pk->dec + intdim + realdim);
  }
  switch (gen->gentyp){
  case AP_GEN_VERTEX:
  case AP_GEN_RAY:
  case AP_GEN_LINE:
    return true;
  default:
    return false;
  }
}
