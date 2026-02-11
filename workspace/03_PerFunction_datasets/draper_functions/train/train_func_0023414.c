el_res2(const EL_INFO *el_info, const REAL_D *Lambda, REAL det,
		    const ELLIPT_EST_D_DATA *data)
{
  const REAL_DD   (*D2uhqp)[DIM_OF_WORLD];
  int             dim = el_info->mesh->dim;
  REAL            val, h2 = h2_from_det(dim, det);
  const REAL      *uh_qpi = NULL;
  int             iq, i, j, mu, nu;
  REAL_D          riq = {};
  const REAL_D    *uh_qp = nil, *grd_uh_qpi = nil;
  const REAL_DD   *grd_uh_qp = nil;
  const QUAD_FAST *quad_fast = data->quad_fast;
  const QUAD      *quad = quad_fast->quad;

  if (data->quad_fast->bas_fcts->degree > 1)
    D2uhqp = D2_uh_d_at_qp(data->quad_fast, Lambda,
			   (const REAL_D *)data->uh_el, nil);
  else
    D2uhqp = nil;

  if (data->f) {
    if (data->f_flag & INIT_UH)
      uh_qp = uh_d_at_qp(quad_fast, (const REAL_D *)data->uh_el, nil);
    else
      uh_qpi = nil;

    if (data->f_flag & INIT_GRD_UH)
      grd_uh_qp = grd_uh_d_at_qp(quad_fast, Lambda,
				 (const REAL_D *)data->uh_el, nil);
    else
      grd_uh_qpi = nil;
  }

  for (val = iq = 0; iq < quad->n_points; iq++)
  {
    if (data->f) {
      if (data->f_flag & INIT_UH)     uh_qpi     = uh_qp[iq];
      if (data->f_flag & INIT_GRD_UH) grd_uh_qpi = grd_uh_qp[iq];

      data->f(el_info, quad, iq, uh_qpi,  grd_uh_qpi, riq);
    }
    else
      SET_DOW(0.0, riq);


    if (D2uhqp) {
      for(mu = 0; mu < DIM_OF_WORLD; mu++)
	for (i = 0; i < DIM_OF_WORLD; i++)
	  for(nu = 0; nu < DIM_OF_WORLD; nu++)
	    for (j = 0; j < DIM_OF_WORLD; j++)
	      riq[mu] -= data->A[i][j][mu][nu] * D2uhqp[iq][nu][i][j];
    }

    val += quad->w[iq]*NRM2_DOW(riq);
  }

  if (data->norm == L2_NORM)
    val = data->C0*h2*h2*det*val;
  else
    val = data->C0*h2*det*val;

  return(val);
}
