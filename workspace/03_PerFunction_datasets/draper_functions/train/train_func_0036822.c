mc_scan_plusargs(char *plusarg)
{
 register struct optlst_t *olp;
 register char *chp;
 int32 arglen, optlen;

 arglen = strlen(plusarg);

 for (olp = __opt_hdr; olp != NULL; olp = olp->optlnxt)
  {

   if (olp->is_bmark || olp->is_emark) continue;

   chp = olp->opt;
   if (*chp != '+') continue;

   if ((optlen = strlen(&(chp[1]))) < arglen) continue;

   if (strncmp(&(chp[1]), plusarg, arglen) != 0) continue;


   return(&(chp[arglen + 1]));
  }

 return(NULL);
}
