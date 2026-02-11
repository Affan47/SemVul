__pvc_call_misctf(struct dcevnt_t *dcep)
{
 int32 pnum, sav_fnam_ind, sav_slin_cnt;
 struct st_t *stp;
 struct expr_t *fcallx;
 struct t_tfcell *tfcp;
 struct tskcall_t *tkcp;
 struct systsk_t *stbp;
 struct sysfunc_t *sfbp;
 struct tfinst_t tfiwrk;
 int32 (*misctf)();

 stp = NULL;
 fcallx = NULL;

 if (dcep->dce_tfunc)
  {
   fcallx = dcep->dceu2.dce_pvc_fcallx;
   sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
   tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]);
   __tfrec = fcallx->lu.x->szu.xfrec;
  }
 else
  {
   stp = dcep->dceu2.dce_pvc_stp;
   tkcp = &(stp->st.stkc);
   stbp = tkcp->tsksyx->lu.sy->el.esytbp;
   tfcp = &(__shadow_veriusertfs[stbp->stsknum - BASE_VERIUSERTFS]);
   __tfrec = tkcp->tkcaux.trec;
  }

 pnum = dcep->dceu.pnum;


 __tfrec->tfargs[pnum].old_pvc_flgs[__inum] = 1;


 if ((misctf = tfcp->misctf) == NULL) return;

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt;
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind;
 __vpilin_cnt = __slin_cnt;


 __tfinst = &tfiwrk;
 __tfinst->callx = NULL;
 __tfinst->tfstp = NULL;
 __tfinst->tfitp = __inst_ptr;
 if (dcep->dce_tfunc) __tfinst->callx = fcallx; else __tfinst->tfstp = stp;


 (*misctf)((int32) tfcp->data, REASON_PARAMVC, pnum);
 __tfinst = NULL;
 __tfrec = NULL;
 __sfnam_ind = sav_fnam_ind; __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
}
