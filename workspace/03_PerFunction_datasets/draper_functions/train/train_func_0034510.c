conn_rtxmr_npin(struct net_t *np, int32 ni1, int32 ni2,
 int32 islhs, int32 npctyp, struct gref_t *grp, int32 chgtyp, char *chgp)
{
 register int32 ii;
 struct net_pin_t *npp;
 struct itree_t *targitp;

 targitp = grp->targu.targitp;

 for (ii = 0; ii < grp->gin_mdp->flatinum; ii++)
  {
   npp = conn2_npin(np, ni1, ni2, islhs, npctyp);
   if (chgtyp != NPCHG_NONE) set_chgsubfld(npp, chgtyp, chgp);
   if (npp->npaux == NULL) npp->npaux = __alloc_npaux();

   npp->npaux->npdownitp = (struct itree_t *) grp->gin_mdp->moditps[ii];


   npp->npaux->npu.filtitp = targitp;

   npp->np_xmrtyp = XNP_RTXMR;
   npp->npproctyp = NP_PROC_FILT;
  }
}
