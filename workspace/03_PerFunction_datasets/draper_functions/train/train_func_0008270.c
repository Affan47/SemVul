cray_bezier_SetColorAt(int sel, Geom *geom, va_list *args) {
  Bezier *b = (Bezier *)geom;
  ColorA *color;
  int vindex, index;
  HPoint3 *pt;

  color = va_arg(*args, ColorA *);
  vindex = va_arg(*args, int);
  (void)va_arg(*args, int);
  (void)va_arg(*args, int *);
  (void)va_arg(*args, int *);
  pt = va_arg(*args, HPoint3 *);

  index = WhichCorner(b, vindex, pt);
  if (index < 0) return (void *)(long)craySetColorAtF(geom, color, 0, NULL);

  b->c[index] = *color;
  return (void *)geom;
}
