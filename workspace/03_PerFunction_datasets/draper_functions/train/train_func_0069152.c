miteUserNew() {
  miteUser *muu;
  int i;

  muu = (miteUser *)calloc(1, sizeof(miteUser));
  if (!muu)
    return NULL;

  muu->umop = airMopNew();
  muu->nsin = NULL;
  muu->nvin = NULL;
  muu->ntin = NULL;
  muu->ntxf = NULL;
  muu->nout = NULL;
  muu->debug = NULL;
  muu->debugArr = NULL;
  muu->ndebug = NULL;

  muu->ntxfNum = 0;
  muu->shadeStr[0] = 0;
  muu->normalStr[0] = 0;
  for (i=0; i<MITE_RANGE_NUM; i++) {
    muu->rangeInit[i] = 1.0;
  }
  muu->normalSide = miteDefNormalSide;
  muu->refStep = miteDefRefStep;
  muu->rayStep = AIR_NAN;
  muu->opacMatters = miteDefOpacMatters;
  muu->opacNear1 = miteDefOpacNear1;
  muu->hctx = hooverContextNew();
  ELL_3V_SET(muu->fakeFrom, AIR_NAN, AIR_NAN, AIR_NAN);
  ELL_3V_SET(muu->vectorD, 0, 0, 0);
  airMopAdd(muu->umop, muu->hctx, (airMopper)hooverContextNix, airMopAlways);
  for (i=gageKernelUnknown+1; i<gageKernelLast; i++) {
    muu->ksp[i] = NULL;
  }
  muu->shape = gageShapeNew();
  muu->gctx0 = gageContextNew();
  airMopAdd(muu->umop, muu->shape, (airMopper)gageShapeNix, airMopAlways);
  airMopAdd(muu->umop, muu->gctx0, (airMopper)gageContextNix, airMopAlways);

  muu->lit = limnLightNew();
  airMopAdd(muu->umop, muu->lit, (airMopper)limnLightNix, airMopAlways);
  muu->normalSide = miteDefNormalSide;
  muu->verbUi = muu->verbVi = -1;
  muu->rendTime = 0;
  muu->sampRate = 0;
  return muu;
}
