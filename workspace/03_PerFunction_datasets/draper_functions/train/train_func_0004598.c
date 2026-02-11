mgrib_findctx( long winid )
{
  struct mgcontext *mgc;

  for(mgc = _mgclist; mgc != NULL; mgc = mgc->next) {
    if(mgc->devno == MGD_RIB && ((mgribcontext *)mgc)->win == winid)
      return mgc;
  }
  return NULL;
}
