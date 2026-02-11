pk_is_leq(ap_manager_t* man, pk_t* pa, pk_t* pb)
{
  pk_internal_t* pk = pk_init_from_manager(man,AP_FUNID_IS_LEQ);

  assert(poly_check(pk,pa));
  assert(poly_check(pk,pb));
  man->result.flag_exact = man->result.flag_best = false;
  if (pk->funopt->algorithm>0)
    poly_chernikova(man,pa,"of the first argument");
  else
    poly_obtain_F(man,pa,"of the first argument");

  if (pk->exn){
    pk->exn = AP_EXC_NONE;
    return false;
  }
  if (!pa->F){
    man->result.flag_exact = man->result.flag_best = true;
    return true;
  }
  if (pk->funopt->algorithm>0)
    poly_chernikova(man,pb,"of the second argument");
  else
    poly_obtain_C(man,pb,"of the second argument");

  if (pk->exn){
    pk->exn = AP_EXC_NONE;
    return false;
  }
  if (!pb->C){
    man->result.flag_exact = man->result.flag_best = (pa->intdim==0);
    return false;
  }
  man->result.flag_exact = man->result.flag_best =
    pa->intdim==0;

  if (pa->C && pa->F && pb->C && pb->F
      && (pa->nbeq < pb->nbeq || pa->nbline > pb->nbline))
    {
     man->result.flag_exact = man->result.flag_best = true;
     return false;
    }
  else {
    man->result.flag_exact = man->result.flag_best = (pa->intdim==0);

    size_t i;
    for (i=0; i<pb->C->nbrows; i++){
      bool sat = do_generators_sat_vector(pk,
					  pa->F,
					  pb->C->p[i],
					  pk->strict &&
					  numint_sgn(pb->C->p[i][polka_eps])<0);
      if (sat==false) return false;
    }
    return true;
  }
}
