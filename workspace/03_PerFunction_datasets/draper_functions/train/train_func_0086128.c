add_stchan_chged_vtx(struct vtx_t *vtxp,
 struct itree_t *vt1_itp)
{
 int32 bi, inum;
 word32 vtxval, st0, st1, lowst;
 struct net_t *np;
 struct vtxlst_t *vtxlp;

 np = vtxp->vnp;
 bi = (vtxp->vi1 == -1) ? 0 : vtxp->vi1;
 inum = vt1_itp->itinum;


 if (np->frc_assgn_allocated
  && np->nu2.qcval[__inum*np->nwid + bi].qc_active)
  {
   vtxp->vtx_forced = TRUE;
   vtxval = (word32) np->nva.bp[inum*np->nwid + bi];
   vtxp->new_vtxval = vtxval;
  }
 else
  {

   vtxval = (word32) np->ntraux->trnva.bp[inum*np->nwid + bi];


   vtxp->vtx_forced = FALSE;
  }
 vtxp->new_vtxval = (byte) vtxval;
 if (vtxval == ST_SUPPLY0 || vtxval == ST_SUPPLY1) vtxp->vtx_supply = TRUE;

 else vtxp->vtx_supply = FALSE;


 st1 = (vtxval >> 2) & 0x7;
 st0 = (vtxval >> 5) & 0x7;
 lowst = (st1 < st0) ? st1 : st0;


 if (__vtxlst_freelst == NULL)
  vtxlp = (struct vtxlst_t *) __my_malloc(sizeof(struct vtxlst_t));
 else
  {
   vtxlp = __vtxlst_freelst;
   __vtxlst_freelst = __vtxlst_freelst->vtxnxt;
  }
 vtxlp->vtxp = vtxp;
 vtxlp->vtx_itp = vt1_itp;
 vtxlp->vtxnxt = NULL;


 if (__stvtxtabend[lowst] != NULL)
  { __stvtxtabend[lowst]->vtxnxt = vtxlp; __stvtxtabend[lowst] = vtxlp; }
 else __stvtxtab[lowst] = __stvtxtabend[lowst] = vtxlp;

 __num_switch_vtxs_processed++;


 if (__debug_flg && __ev_tracing)
  {
   __dbg_msg("** vertex %s.%s level %d added to incremental perturb list\n",
    __msg2_blditree(__xs, vtxlp->vtx_itp), to_vtx(__xs2, vtxp), lowst);
  }
 return(vtxlp);
}
