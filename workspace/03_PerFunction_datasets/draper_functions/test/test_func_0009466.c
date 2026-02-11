vect_PointList_fillin(int sel, Geom *geom, va_list *args) {
  Vect *v = (Vect *)geom;
  TransformPtr t;
  HPoint3 *plist;

  t = va_arg(*args, TransformPtr);
  (void)va_arg(*args, int);
  plist = va_arg(*args, HPoint3 *);
  memcpy(plist, v->p, v->nvert * sizeof(HPoint3));
  HPt3TransformN(t, plist, plist, v->nvert);
  return((void *)plist);
}
