mesh_PointList_fillin(int sel, Geom *geom, va_list *args) {
  HPoint3 *pt;
  TransformPtr t;
  Mesh *m = (Mesh *)geom;

  t = va_arg(*args, TransformPtr);
  (void)va_arg(*args, int);
  pt = va_arg(*args, HPoint3 *);

  memcpy(pt, m->p, m->nu * m->nv * sizeof(HPoint3));
  HPt3TransformN(t, pt, pt, m->nu * m->nv);

  return pt;
}
