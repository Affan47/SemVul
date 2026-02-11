__pli_func_calltf(struct expr_t *fcallx)
{
 int32 nbytes, sav_fnam_ind, sav_slin_cnt;
 struct t_tfcell *tfcp;
 struct sysfunc_t *sfbp;
 struct xstk_t *xsp;
 struct tfinst_t tfiwrk;
 int32 (*calltf_func)();

 sfbp = fcallx->lu.x->lu.sy->el.esyftbp;
 tfcp = &(__shadow_veriusertfs[sfbp->syfnum - BASE_VERIUSERTFS]);
 __tfrec = fcallx->lu.x->szu.xfrec;

 if ((calltf_func = tfcp->calltf) == NULL)
  {
   push_xstk_(xsp, __tfrec->fretsiz);
   one_allbits_(xsp->ap, xsp->xslen);
   one_allbits_(xsp->bp, xsp->xslen);
   __tfrec = NULL;
   return;
  }

 sav_fnam_ind = __sfnam_ind; sav_slin_cnt = __slin_cnt;
 __sfnam_ind = (int32) __tfrec->tffnam_ind; __slin_cnt = __tfrec->tflin_cnt;
 __vpifnam_ind = __sfnam_ind;
 __vpilin_cnt = __slin_cnt;


 __tfinst = &tfiwrk;
 __tfinst->callx = fcallx;
 __tfinst->tfstp = NULL;
 __tfinst->tfitp = __inst_ptr;


 (*calltf_func)((int32) tfcp->data, REASON_CALLTF);


 nbytes = 2*wlen_(__tfrec->fretsiz)*WRDBYTES;
 push_xstk_(xsp, __tfrec->fretsiz);

 memcpy(xsp->ap, __tfrec->tfargs[0].arg.awp, nbytes);

 __sfnam_ind = sav_fnam_ind;
 __slin_cnt = sav_slin_cnt;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;
 __tfrec = NULL;
 __tfinst = NULL;
}
