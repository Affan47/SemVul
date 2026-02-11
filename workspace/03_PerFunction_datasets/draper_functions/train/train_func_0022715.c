drawer_post_xform(int id, Transform T)
{
  TransformStruct ts;
  Transform N, NInv;
  DObject *dobj;

  if((dobj = drawer_get_object(id)) == NULL) {
    return;
  }

  ts.h = NULL;

  if (ISGEOM(id)) {
    GeomGet(((DGeom *)dobj)->Item, CR_AXIS, ts.tm);
    if (((DGeom *)dobj)->citizenship == ORDINARY) {
      GeomGet(((DGeom *)dobj)->Inorm, CR_AXIS, N);
      TmInvert(N, NInv);
      TmConcat(NInv, T, T);
      TmConcat(T, N, T);
    }
  } else {
    CamGet(((DView *)dobj)->cam, CAM_C2W, ts.tm);
  }
  TmConcat(T, ts.tm, ts.tm);
  gv_xform_set(id, &ts);
}
