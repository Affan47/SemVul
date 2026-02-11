make_light(Point3 axis, Color *color)
{
  Geom *g;
  Transform t;
  Appearance *ap;

  ap = ApCreate(AP_MtSet, MT_EDGECOLOR, color, MT_END, AP_END);
  lxform(t, axis);
  g = GeomCreate("inst", CR_GEOM, ray, CR_NOCOPY, CR_APPEAR, ap, CR_END);
  if (g == NULL) {
    fprintf(stderr, "Couldn't create inst\n");
    return NULL;
  }
  InstTransformTo((Inst *)g, t, NULL);
  return g;
}
