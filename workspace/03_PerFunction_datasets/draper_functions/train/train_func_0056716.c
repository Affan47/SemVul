__add_dctldel_pnp(struct st_t *stp)
{
 register struct paramlst_t *pmp;
 int32 sav_fnam_ind, sav_slin_cnt;
 struct delctrl_t *dctp;
 struct paramlst_t *pdels;
 struct expr_t *dxp;
 struct parmnet_pin_t tmpl_pnp;

 init_pnp(&tmpl_pnp);
 tmpl_pnp.pnptyp = PNP_PROCDCTRL;

 dctp = stp->st.sdc;
 tmpl_pnp.elpnp.edctp = dctp;
 pdels = dctp->dc_du.pdels;

 tmpl_pnp.pnplp = pdels;

 sav_fnam_ind = __sfnam_ind;
 sav_slin_cnt = __slin_cnt;
 __sfnam_ind = (int32) stp->stfnam_ind;
 __slin_cnt = stp->stlin_cnt;


 __nd_parmpnp_free = TRUE;

 if (pdels->pmlnxt != NULL) __misc_terr(__FILE__, __LINE__);

 for (pmp = pdels; pmp != NULL; pmp = pmp->pmlnxt)
  { dxp = pmp->plxndp; addto_parmnplst(dxp, &tmpl_pnp); }

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
}
