quad_2_10_0(const EL_INFO *el_info, const DOWB_FILL_INFO *info)
{
  DECL_DOWB_BB(LALt);
  DECL_DOWB_B(Lb1);
  DECL_DOWB_C(c);
  REAL  (*grd_psi)[N_LAMBDA], *psi, (*grd_phi)[N_LAMBDA], *phi;
  int              iq, i, j;
  const QUAD_FAST  *psi_fast, *phi_fast;
  const QUAD       *quad;
  int              n_lambda = el_info->mesh->dim + 1;
  DOWBM_TYPE       type = info->type;
  ASSIGN_MAT(mat, info->element_matrix);
  DECL_SOMEVAR(val);
  DECL_SOMEVAR(tmp);

  quad     = info->quad[2];
  psi_fast = info->psi_quad_fast[2];
  phi_fast = info->phi_quad_fast[2];

#undef BODY
#define BODY(F, C, P, S)						\
  for (iq = 0; iq < quad->n_points; iq++) {				\
    GET_VALUE(S, LALt, info->LALt,					\
	      (el_info, quad, iq, info->user_data));			\
    GET_VALUE(S, Lb1, info->Lb1,					\
	      (el_info, quad, iq, info->user_data));			\
    GET_VALUE(S, c, info->c,						\
	      (el_info, quad, iq, info->user_data));			\
									\
    grd_psi = psi_fast->grd_phi[iq];					\
    grd_phi = phi_fast->grd_phi[iq];					\
									\
    psi     = psi_fast->phi[iq];					\
    phi     = phi_fast->phi[iq];					\
									\
    for (i = 0; i < info->n_row; i++) {					\
      for (j = 0; j < info->n_col; j++) {				\
	F##AXPY_DOW(phi[j],						\
		    F##AXPY_DOW(psi[i], C c.S,				\
				F##btv(n_lambda, Lb1.S, grd_psi[i],	\
				       C P tmp.S)),			\
		    F##utAv(n_lambda, grd_psi[i], LALt.S, grd_phi[j],	\
			    C P val.S));				\
	F##AXPY_DOW(quad->w[iq], C P val.S, C P mat.S[i][j]);		\
      }									\
    }									\
  }
  EMIT_BODY_SWITCH(type);
}
