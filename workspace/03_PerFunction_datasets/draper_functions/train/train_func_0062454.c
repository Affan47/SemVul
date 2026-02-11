tenExpand(Nrrd *nout, const Nrrd *nin, double scale, double thresh) {
  static const char me[]="tenExpand";
  size_t N, I, sx, sy, sz;
  float *seven, *nine;

  if (!( nout && nin && AIR_EXISTS(thresh) )) {
    biffAddf(TEN, "%s: got NULL pointer or non-existent threshold", me);
    return 1;
  }
  if (nout == nin) {
    biffAddf(TEN, "%s: sorry, need different nrrds for input and output", me);
    return 1;
  }
  if (tenTensorCheck(nin, nrrdTypeFloat, AIR_TRUE, AIR_TRUE)) {
    biffAddf(TEN, "%s: ", me);
    return 1;
  }

  sx = nin->axis[1].size;
  sy = nin->axis[2].size;
  sz = nin->axis[3].size;
  N = sx*sy*sz;
  if (nrrdMaybeAlloc_va(nout, nrrdTypeFloat, 4,
                        AIR_CAST(size_t, 9), sx, sy, sz)) {
    biffMovef(TEN, NRRD, "%s: trouble", me);
    return 1;
  }
  for (I=0; I<=N-1; I++) {
    seven = (float*)(nin->data) + I*7;
    nine = (float*)(nout->data) + I*9;
    if (seven[0] < thresh) {
      ELL_3M_ZERO_SET(nine);
      continue;
    }
    TEN_T2M(nine, seven);
    ELL_3M_SCALE(nine, AIR_CAST(float, scale), nine);
  }
  if (nrrdAxisInfoCopy(nout, nin, NULL,
                       NRRD_AXIS_INFO_SIZE_BIT)) {
    biffMovef(TEN, NRRD, "%s: trouble", me);
    return 1;
  }


  nout->axis[0].kind = nrrdKind3DMatrix;
  if (nrrdBasicInfoCopy(nout, nin,
                        NRRD_BASIC_INFO_ALL ^ NRRD_BASIC_INFO_SPACE)) {
    biffAddf(TEN, "%s:", me);
    return 1;
  }


  return 0;
}
