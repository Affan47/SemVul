L2_err_d(const REAL *(*u)(const REAL_D, REAL_D),
	       const DOF_REAL_D_VEC *uh,
	       const QUAD *quad, int rel_err, REAL *(*rw_err_el)(EL *),
	       REAL *max_l2_err2)
{
  FUNCNAME("L2_err_d");
  ERR_TRAVERSE_DATA td[1] = {{0}};
  const FE_SPACE *fe;

  if (!(p_u_d = u))
  {
    ERROR("no function u specified; doing nothing\n");
    return(0.0);
  }
  if (!(err_uh_d = uh)  ||  !(fe = uh->fe_space))
  {
    ERROR("no discrete function or no fe_space for it; doing nothing\n");
    return(0.0);
  }
  if (!uh->vec)
  {
    ERROR("no coefficient vector at discrete solution ; doing nothing\n");
    return(0.0);
  }
  if (!(bas_fcts = fe->bas_fcts))
  {
    ERROR("no basis functions at discrete solution ; doing nothing\n");
    return(0.0);
  }
  if (!quad)
    quad = get_quadrature(fe->mesh->dim, 2*bas_fcts->degree -2);
  quad_fast = get_quad_fast(bas_fcts, quad, INIT_PHI);

  get_real_d_vec_el = bas_fcts->get_real_d_vec;

  relative = rel_err;

  rw_error = rw_err_el;

  td->max_err = td->l2_err_2 = td->l2_norm2 = 0.0;
  mesh_traverse(fe->mesh, -1, FILL_COORDS|CALL_LEAF_EL, l2_err_fct_d, td);

  if (relative)
  {
    td->rel_norm2 = td->l2_norm2+1.e-15;
    if (rw_error)  mesh_traverse(fe->mesh, -1, CALL_LEAF_EL, rel_fct, td);
    td->l2_err_2 /= td->rel_norm2;
  }

  if (max_l2_err2) *max_l2_err2 = td->max_err;

  return(sqrt(td->l2_err_2));
}
