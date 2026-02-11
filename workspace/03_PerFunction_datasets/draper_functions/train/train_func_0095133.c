oct_add_epsilon(ap_manager_t* man, oct_t* a, ap_scalar_t* epsilon)
{
  oct_internal_t* pr = oct_init_from_manager(man,AP_FUNID_WIDENING,2);
  oct_t* r = oct_alloc_internal(pr,a->dim,a->intdim);
  bound_t* m;
  m = a->m ? a->m : a->closed;
  if (m) {
    size_t i;

    bound_set_int(pr->tmp[0],0);
    for (i=0;i<matsize(a->dim);i++) {
      if (bound_infty(m[i])) continue;
      if (bound_sgn(m[i])>=0)
	bound_max(pr->tmp[0],pr->tmp[0],m[i]);
      else {
	bound_neg(pr->tmp[1],m[i]);
	bound_max(pr->tmp[0],pr->tmp[0],pr->tmp[1]);
      }
    }

    bound_of_scalar(pr,pr->tmp[1],epsilon,false,false);
    bound_mul(pr->tmp[0],pr->tmp[0],pr->tmp[1]);

    r->m = hmat_alloc(pr,r->dim);
    for (i=0;i<matsize(r->dim);i++)
      bound_add(r->m[i],m[i],pr->tmp[0]);
  }
  return r;
}
