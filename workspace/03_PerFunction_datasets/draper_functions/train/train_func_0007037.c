FcExprMatrixFree (FcExprMatrix *m)
{
  if (!m)
    return;

  FcExprDestroy (m->xx);
  FcExprDestroy (m->xy);
  FcExprDestroy (m->yx);
  FcExprDestroy (m->yy);

  free (m);
}
