mark_gia_rng_params(struct mod_t *pmdp)
{
 register int32 gi, ii;
 struct giarr_t *giap;

 if (pmdp->mgarr != NULL)
  {
   for (gi = 0; gi < pmdp->mgnum; gi++)
    {
     if ((giap = pmdp->mgarr[gi]) == NULL) continue;

     if (in_giarng_markparam(giap, giap->giax1))
      pmdp->mpndprm_ingirng = TRUE;
     if (in_giarng_markparam(giap, giap->giax2))
      pmdp->mpndprm_ingirng = TRUE;
    }
  }

 if (pmdp->miarr != NULL)
  {
   for (ii = 0; ii < pmdp->minum; ii++)
    {
     if ((giap = pmdp->miarr[ii]) == NULL) continue;

     if (in_giarng_markparam(giap, giap->giax1))
      pmdp->mpndprm_ingirng = TRUE;
     if (in_giarng_markparam(giap, giap->giax2))
      pmdp->mpndprm_ingirng = TRUE;
    }
  }
}
