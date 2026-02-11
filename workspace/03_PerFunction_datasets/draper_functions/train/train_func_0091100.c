free_all_param_vals()
{
 register int32 pi;
 register struct mod_t *mdp;
 register struct net_t *parm_np;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mprmnum == 0) continue;

   for (pi = 0, parm_np = &(mdp->mprms[0]); pi < mdp->mprmnum; pi++, parm_np++)
    {

     if (parm_np->nu2.wp == NULL) __misc_terr(__FILE__, __LINE__);

     __my_free((char *) parm_np->nu2.wp, 2*WRDBYTES*wlen_(parm_np->nwid));
     parm_np->nu2.wp = NULL;
    }
  }
}
