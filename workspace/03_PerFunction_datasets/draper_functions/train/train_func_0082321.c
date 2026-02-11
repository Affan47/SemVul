bezier_PointList_fillin(int sel, Geom *geom, va_list *args) {
  int i = 0;
  TransformPtr t;
  HPoint3 *pt;
  Bezier *b = (Bezier *)geom;

  t = va_arg(*args, TransformPtr);
  (void)va_arg(*args, int);
  pt = va_arg(*args, HPoint3 *);

  if (b->CtrlPnts != NULL) {
    if (b->dimn == 3) {
      for (i = 0; i < (b->degree_u + 1) * (b->degree_v + 1); i++)
	HPt3From(&pt[i], b->CtrlPnts[i*3], b->CtrlPnts[i*3 + 1],
		 b->CtrlPnts[i*3 + 2], 1.0);
    } else {
      if (b->dimn == 4) {
	for (i = 0; i < (b->degree_u + 1) * (b->degree_v + 1); i++)
	  HPt3From(&pt[i], b->CtrlPnts[i*4], b->CtrlPnts[i*4 + 1],
		   b->CtrlPnts[i*4 + 2], b->CtrlPnts[i*4 + 3]);
      } else {
	OOGLError(1, "Bezier patch of unfamiliar dimensions.");
	OOGLFree(pt);
	return NULL;
      }
    }
  }

#ifdef DONT_DO_THIS
  if (b->flag & BEZ_ST) {
    HPt3From(&pt[i], b->STCords[0], b->STCords[1], b->STCords[2],
	     b->STCords[3]);
    HPt3From(&pt[i+1], b->STCords[4], b->STCords[5], b->STCords[6],
	     b->STCords[7]);
  }
#endif

  HPt3TransformN(t, pt, pt, i+1);

  return pt;
}
