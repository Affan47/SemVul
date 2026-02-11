form_C0j (const GRETL_VAR *var, gretl_matrix *C0j,
	  gretl_matrix *et, gretl_matrix *ej,
	  int j)
{
    int i, t;

    gretl_matrix_zero(C0j);

    for (t=j; t<var->T; t++) {

	for (i=0; i<var->neqns; i++) {
	    et->val[i] = gretl_matrix_get(var->E, t, i);
	    ej->val[i] = gretl_matrix_get(var->E, t-j, i);
	}

	gretl_matrix_multiply_mod(et, GRETL_MOD_TRANSPOSE,
				  ej, GRETL_MOD_NONE,
				  C0j, GRETL_MOD_CUMULATE);
    }

    gretl_matrix_divide_by_scalar(C0j, var->T);
}
