__ndst_eval_xpr(struct expr_t *ndp)
{
 byte *sbp;
 struct xstk_t *stxsp;


 push_xstk_(stxsp, 4*ndp->szu.xclen);
 sbp = (byte *) stxsp->ap;
 ndst_eval2_xpr(sbp, ndp);
 return(stxsp);
}
