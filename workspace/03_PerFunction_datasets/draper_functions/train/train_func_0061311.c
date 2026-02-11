poly_add_ray_array(bool lazy,
			ap_manager_t* man,
			pk_t* po, pk_t* pa, ap_generator0_array_t* array)
{
  bool exact;
  matrix_t* mat;

  pk_internal_t* pk = (pk_internal_t*)man->internal;

  man->result.flag_best = man->result.flag_exact = true;


  if (lazy){
    poly_obtain_F(man,pa,"of the argument");
  } else {
    poly_chernikova(man,pa,"of the argument");
  }
  if (pk->exn){
    pk->exn = AP_EXC_NONE;
    if (!pa->F){
      man->result.flag_best = man->result.flag_exact = false;
      poly_set_top(pk,po);
      return;
    }
  }

  if ( !pa->C && !pa->F){
    poly_set(po,pa);
    return;
  }
  exact = matrix_set_ap_generator0_array(pk,&mat,array,pa->intdim,pa->realdim);
  matrix_sort_rows(pk,mat);

  if (!lazy) poly_obtain_satF(pa);
  poly_dual(po);
  if (po!=pa) poly_dual(pa);
  poly_meet_matrix(false,lazy,man,po,pa,mat);
  poly_dual(po);
  if (po!=pa) poly_dual(pa);
  matrix_free(mat);
  man->result.flag_exact = exact;
}
