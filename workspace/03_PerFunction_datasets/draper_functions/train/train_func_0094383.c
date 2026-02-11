init_add_vtx_and_subtree(struct vtx_t *vtxp,
 struct itree_t *vt1_itp)
{
 register struct edge_t *ep;
 int32 bi, inum;
 word32 vtxval, lowst, st0, st1;
 struct vtxlst_t *vtxlp;
 struct net_t *np;
 struct itree_t *oside_itp;

 np = vtxp->vnp;
 bi = vtxp->vi1;
 bi = (bi == -1) ? 0 : bi;

 inum = vt1_itp->itinum;

 vtxp->old_vtxval = np->nva.bp[inum*np->nwid + bi];


 vtxval = (word32) np->ntraux->trnva.bp[inum*np->nwid + bi];


 vtxp->new_vtxval = (byte) vtxval;
 if (vtxval == ST_SUPPLY0 || vtxval == ST_SUPPLY1) vtxp->vtx_supply = TRUE;


 st1 = (vtxval >> 2) & 0x7;
 st0 = (vtxval >> 5) & 0x7;
 lowst = (int32) ((st1 < st0) ? st1 : st0);

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

 vtxp->vtx_mark = TRUE;
 __num_switch_vtxs_processed++;


 if (__debug_flg && __ev_tracing)
  {
   __dbg_msg("** vertex %s.%s level %d added to perturb list\n",
    __msg2_blditree(__xs, vtxlp->vtx_itp), to_vtx(__xs2, vtxp), lowst);
  }

 for (ep = vtxp->vedges; ep != NULL; ep = ep->enxt)
  {
   if (ep->ev2->vtx_mark) continue;


   if (ep->edgoside_itp != NULL) oside_itp = ep->edgoside_itp;
   else oside_itp = vt1_itp;

   init_add_vtx_and_subtree(ep->ev2, oside_itp);
  }
}
