mark_stdr_inout_wired_logic(void)
{
 register int32 ii, pi;
 register struct mod_t *mdp;
 int32 pnum;
 struct mod_pin_t *mpp;
 struct inst_t *ip;
 struct mod_t *imdp;
 struct expr_t *xp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {

   for (pi = 0; pi < mdp->mpnum; pi++)
    {
     mpp = &(mdp->mpins[pi]);
     if (mpp->mptyp != IO_BID) continue;

     if (has_non_stren_wired_net(mpp->mpref))
      mark_stwires(mdp, mpp->mpref);
    }


   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       if (mpp->mptyp != IO_BID) continue;

       xp = ip->ipins[pi];
       if (has_non_stren_wired_net(xp)) mark_stwires(imdp, xp);
      }
    }
  }
}
