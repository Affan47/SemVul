prop_stsup(void)
{
 register int32 pi, ii;
 register struct mod_t *smdp;
 register struct inst_t *ip;
 int32 mlevel, pnum, skip_giarr;
 struct mod_pin_t *mpp;
 struct mod_t *imdp;
 struct giarr_t *giap;
 struct expr_t *xp;

 giap = NULL;

 for (mlevel = 1; mlevel <= __dagmaxdist; mlevel++)
  {
   for (smdp = __mdlevhdr[mlevel]; smdp != NULL; smdp = smdp->mlevnxt)
    {

     for (ii = 0; ii < smdp->minum; ii++)
      {
       ip = &(smdp->minsts[ii]);
       if (smdp->miarr != NULL && (giap = smdp->miarr[ii]) != NULL)
        skip_giarr = TRUE;
       else skip_giarr = FALSE;

       imdp = ip->imsym->el.emdp;
       if ((pnum = imdp->mpnum) == 0) goto nxt_inst;
       for (pi = 0; pi < pnum; pi++)
        {
         mpp = &(imdp->mpins[pi]);
         xp = ip->ipins[pi];
	 if (mpp->mptyp == IO_IN) continue;


         if (chk_hasst_wires(imdp, mpp->mpref))
          mark_stwires(smdp, xp);
	}
nxt_inst:
         if (skip_giarr) ii += (__get_giarr_wide(giap) - 1);
      }
    }
  }
}
