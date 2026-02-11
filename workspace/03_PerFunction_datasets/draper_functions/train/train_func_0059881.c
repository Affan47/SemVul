save_bidandtran_npps(void)
{
 register struct net_pin_t *npp;
 register int32 ni;
 register struct mod_t *mdp;
 register struct net_t *np;
 struct net_pin_t *last_npp, *npp2;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum == 0) continue;
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     for (last_npp = NULL, npp = np->ndrvs; npp != NULL;)
      {

       npp2 = npp->npnxt;
       if (npp->npntyp == NP_BIDMDPRT || npp->npntyp == NP_BIDICONN
        || npp->npntyp == NP_TRAN)
        {

         if (last_npp == NULL) np->ndrvs = npp->npnxt;
         else last_npp->npnxt = npp->npnxt;


         npp->npnxt = np->ntraux->tran_npps;
         np->ntraux->tran_npps = npp;
        }
       else last_npp = npp;
       npp = npp2;
      }
    }
  }
}
