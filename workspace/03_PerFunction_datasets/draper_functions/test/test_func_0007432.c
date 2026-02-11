__reinit_regwir_putvrec(struct net_t *np, int32 insts)
{
 register int32 ii;
 register struct dltevlst_t *dlp, *dlp2, *last_dlp;

 for (ii = 0; ii < insts; ii++)
  {

   if ((dlp = np->regwir_putv_tedlst[ii]) == NULL) continue;
   last_dlp = NULL;
   for (dlp2 = dlp; dlp2 != NULL; dlp2 = dlp2->terp) last_dlp = dlp2;
   last_dlp->terp = __dltevfreelst;
   __dltevfreelst = dlp;
  }
}
