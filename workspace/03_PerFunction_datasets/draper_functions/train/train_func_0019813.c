mrendUserNew(void) {
  mrendUser *uu;
  int i;

  uu = AIR_CALLOC(1, mrendUser);
  uu->nin = NULL;
  uu->kind = NULL;
  uu->rayStep = 0.0;
  uu->whatq = gageSclUnknown;
  uu->measr = nrrdMeasureUnknown;
  for (i=gageKernelUnknown+1; i<gageKernelLast; i++) {
    uu->ksp[i] = NULL;
  }
  uu->shape = gageShapeNew();
  uu->gctx0 = gageContextNew();
  uu->hctx = hooverContextNew();
  uu->outS = NULL;
  uu->mrmop = airMopNew();
  airMopAdd(uu->mrmop, uu->shape, (airMopper)gageShapeNix, airMopAlways);
  airMopAdd(uu->mrmop, uu->gctx0, (airMopper)gageContextNix, airMopAlways);
  airMopAdd(uu->mrmop, uu->hctx, (airMopper)hooverContextNix, airMopAlways);
  return uu;
}
