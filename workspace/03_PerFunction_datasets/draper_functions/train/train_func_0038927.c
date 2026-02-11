poly_asssub_texpr_array(bool assign,
			      bool lazy,
			      ap_manager_t* man,
			      bool destructive,
			      pk_t* pa,
			      ap_dim_t* tdim, ap_texpr0_t** texpr, size_t size,
			      pk_t* pb)
{
  pk_t* po;
  pk_internal_t* pk = (pk_internal_t*)man->internal;


  if (!lazy){
    poly_chernikova(man,pa,"of the argument");
    if (pk->exn){
      pk->exn = AP_EXC_NONE;
      man->result.flag_best = man->result.flag_exact = false;
      if (destructive){
	poly_set_top(pk,pa);
	return pa;
      } else {
	return pk_top(man,pa->intdim,pa->realdim);
      }
    }
  }

  if (!pa->C && !pa->F){
    man->result.flag_best = man->result.flag_exact = true;
    return destructive ? pa : pk_bottom(man,pa->intdim,pa->realdim);
  }

  if (ap_texpr0_array_is_scalar(texpr,size) &&
      ap_texpr0_array_is_interval_linear(texpr,size)){
    ap_abstract0_t abs;
    abs.value = pa;
    abs.man = man;
    if (size==1){
      ap_linexpr0_t* linexpr0 =
	ap_intlinearize_texpr0(man,&abs,texpr[0],NULL,
			       AP_SCALAR_MPQ,false);
      po = poly_asssub_linexpr_det(assign,man,destructive,
				   pa, tdim[0], linexpr0);
      ap_linexpr0_free(linexpr0);
    }
    else {
      ap_linexpr0_t** tlinexpr =
	ap_intlinearize_texpr0_array(man,&abs,texpr,size,NULL,
				     AP_SCALAR_MPQ,false);
      po = poly_asssub_linexpr_array_det(assign,man,destructive,
					 pa,tdim,tlinexpr,size);
      ap_linexpr0_array_free(tlinexpr,size);
    }
    if (pb){
      poly_meet(true,lazy,man,po,po,pb);
    }
  }
  else {
    po = ap_generic_asssub_texpr_array(assign,man,destructive,pa,tdim,texpr,size,pb);
  }

  if (!lazy){
    poly_chernikova(man,po,"of the result");
    if (pk->exn){
      pk->exn = AP_EXC_NONE;
      man->result.flag_best = man->result.flag_exact = false;
      if (pb) poly_set(po,pb); else poly_set_top(pk,po);
      return po;
    }
  }

  if (pk->funopt->flag_best_wanted || pk->funopt->flag_exact_wanted){
    man->result.flag_best = ap_texpr0_array_is_interval_linear(texpr,size);
    man->result.flag_exact = man->result.flag_best;
  }
  else {
    man->result.flag_best = man->result.flag_exact = false;
  }
  return po;
}
