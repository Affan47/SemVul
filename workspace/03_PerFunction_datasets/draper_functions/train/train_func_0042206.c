pushT(mgNDctx *NDctx, Transform T)
{
  NDstuff *nds = (NDstuff *)NDctx;

  TmNApplyT3TN(T, NULL, nds->T);

  if (nds->Tc) {
    TmNApplyT3TN(T, NULL, nds->Tc);
  }

#if 0
  compute_mg_factor(nds);
  mgtransform(nds->MGFactor);
#endif
}
