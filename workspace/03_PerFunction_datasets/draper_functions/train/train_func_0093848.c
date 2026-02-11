HandleUnregisterJust(Handle **hp, Ref *obj, void *info,
			  void (*update) P((Handle **, Ref *, void *)))
{
  Handle *h;
  HRef *rp, *rnext;

  if(hp == NULL || (h = *hp) == NULL) {
    return;
  }

  DblListIterate(&h->refs, HRef, node, rp, rnext) {
    if(rp->hp == hp &&
       (obj == NULL || rp->parentobj == obj) &&
       (info == NULL || rp->info == info) &&
       (update == NULL || rp->update == update)) {
      DblListDelete(&rp->node);
      FREELIST_FREE(HRef, rp);
      REFPUT(h);
    }
  }
}
