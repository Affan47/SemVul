add_vtx_to_offlist(struct vtx_t *vtxp)
{
 register struct vtxlst_t *vtxlp;
 register struct edge_t *ep;


 if (__vtxlst_freelst == NULL)
  vtxlp = (struct vtxlst_t *) __my_malloc(sizeof(struct vtxlst_t));
 else
  {
   vtxlp = __vtxlst_freelst;
   __vtxlst_freelst = __vtxlst_freelst->vtxnxt;
  }

 vtxlp->vtxp = vtxp;
 vtxlp->vtxnxt = NULL;
 vtxp->vtx_mark2 = TRUE;


 if (__off_vtxlst_end != NULL)
  { __off_vtxlst_end->vtxnxt = vtxlp; __off_vtxlst_end = vtxlp; }
 else __off_vtxlst_end = __off_vtxlst_hdr = vtxlp;


 for (ep = vtxp->vedges; ep != NULL; ep = ep->enxt)
  {
   if (ep->ev2->vtx_mark2) continue;

   add_vtx_to_offlist(ep->ev2);
  }
}
