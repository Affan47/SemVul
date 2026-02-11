__initialize_dces(struct mod_t *mdp)
{
 register int32 i, ni;
 register struct net_t *np;
 register struct net_pin_t *npp;
 int32 insts;
 word64 tim0;
 struct tchg_t *tchgp;
 struct chktchg_t *chktcp;
 struct task_t *tskp;

 insts = mdp->flatinum;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (np->ntyp == N_EVENT) goto skip_spec;


   if (mdp->mspfy != NULL)
    {
     tim0 = 0ULL;
     for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
      {
       if (npp->npntyp != NP_TCHG) continue;

       switch ((byte) npp->chgsubtyp) {
        case NPCHG_TCSTART: case NPCHG_PTHSRC:
         tchgp = npp->elnpp.etchgp;
         reinit_npp_oldval(tchgp->oldval, np, mdp);
         for (i = 0; i < insts; i++) tchgp->lastchg[i] = tim0;
         break;
        case NPCHG_TCCHK:
         chktcp = npp->elnpp.echktchgp;
         reinit_npp_oldval(chktcp->chkoldval, np, mdp);
         for (i = 0; i < insts; i++) chktcp->chklastchg[i] = tim0;
         break;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
    }
skip_spec:
   __init_1net_dces(np, mdp);
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   if (tskp->trnum == 0) continue;
   for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
    {

     __init_1net_dces(np, mdp);
    }
  }
}
