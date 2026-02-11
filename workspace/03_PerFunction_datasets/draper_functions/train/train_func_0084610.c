__vpi_sysf_calltf(struct expr_t *fcallx)
{
 int32 stf_ind;
 struct sysfunc_t *sfbp;
 struct xstk_t *xsp;
 struct systftab_t *stftabp;
 p_vpi_systf_data stfdp;
 int32 (*vpicalltf_func)();

 sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
 stf_ind = sfbp->syfnum - (__last_veriusertf + 1);
 stftabp = &(__systftab[stf_ind]);
 stfdp = (p_vpi_systf_data) stftabp->vpi_sytfdat;
 __cur_sysf_expr = fcallx;


 push_xstk_(xsp, stftabp->sfu.sfbp->retwid);
 one_allbits_(xsp->ap, xsp->xslen);
 one_allbits_(xsp->bp, xsp->xslen);
 __cur_sysf_xsp = xsp;


 if ((vpicalltf_func = stfdp->calltf) == NULL) { return; }
 __vpifnam_ind = __sfnam_ind;
 __vpilin_cnt = __slin_cnt;


 (*vpicalltf_func)(stfdp->user_data);

 __cur_sysf_xsp = NULL;
 __cur_sysf_expr = NULL;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
}
