oct_add_ray_array(ap_manager_t* man,
			 bool destructive, oct_t* a,
			 ap_generator0_array_t* array)
{
  oct_internal_t* pr =
    oct_init_from_manager(man,AP_FUNID_ADD_RAY_ARRAY,2*(a->dim+2));
  bound_t *m;
  if (pr->funopt->algorithm>=0) oct_cache_closure(pr,a);
  m = a->closed ? a->closed : a->m;
  if (!m)

    return oct_set_mat(pr,a,NULL,NULL,destructive);
  else {
    size_t i;
    if (!destructive) m = hmat_copy(pr,m,a->dim);
    hmat_add_generators(pr,m,a->dim,array);

    man->result.flag_exact = false;
    if (num_incomplete || a->intdim) flag_incomplete;
    else if (!a->closed) flag_algo;
    else if (pr->conv) flag_conv;
    return oct_set_mat(pr,a,m,NULL,destructive);
  }
}
