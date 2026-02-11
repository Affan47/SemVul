cray_inst_SetColorAt(int sel, Geom *geom, va_list *args) {
  ColorA *c = va_arg(*args, ColorA *);
  int vindex = va_arg(*args, int), findex = va_arg(*args, int),
  *edge = va_arg(*args, int *), *gpath = va_arg(*args, int *);
  HPoint3 *pt = va_arg(*args, HPoint3 *);
  return (void *)(long)(craySetColorAt(((Inst *)geom)->geom, c, vindex,
				       findex, edge,
				       gpath == NULL ? NULL : gpath + 1, pt));
}
