art_drect_svp_union (ArtDRect *bbox, const ArtSVP *svp)
{
  int i;

  for (i = 0; i < svp->n_segs; i++)
    {
      art_drect_union (bbox, bbox, &svp->segs[i].bbox);
    }
}
