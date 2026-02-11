drawer_transform_ndstuff(NDstuff *nds, TransformN *T)
{
  nds->T = TmNConcat(T, nds->W2C, nds->T);
  if (nds->W2c) {
    nds->Tc = TmNConcat(T, nds->W2c, nds->Tc);
  }

#if 0
  compute_mg_factor(nds);
  mgtransform(nds->MGFactor);
#endif
}
