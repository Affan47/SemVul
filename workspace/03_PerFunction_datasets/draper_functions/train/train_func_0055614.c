tenAnisoVolume(Nrrd *nout, const Nrrd *nin, int aniso, double confThresh) {
  static const char me[]="tenAnisoVolume";
  size_t N, I;
  float *out, *in, *tensor;
  int map[NRRD_DIM_MAX];
  size_t sx, sy, sz, size[3];

  if (tenTensorCheck(nin, nrrdTypeFloat, AIR_TRUE, AIR_TRUE)) {
    biffAddf(TEN, "%s: didn't get a tensor nrrd", me);
    return 1;
  }
  if (airEnumValCheck(tenAniso, aniso)) {
    biffAddf(TEN, "%s: invalid aniso (%d)", me, aniso);
    return 1;
  }
  confThresh = AIR_CLAMP(0.0, confThresh, 1.0);

  size[0] = sx = nin->axis[1].size;
  size[1] = sy = nin->axis[2].size;
  size[2] = sz = nin->axis[3].size;
  N = sx*sy*sz;
  if (nrrdMaybeAlloc_va(nout, nrrdTypeFloat, 3, sx, sy, sz)) {
    biffMovef(TEN, NRRD, "%s: trouble", me);
    return 1;
  }
  out = (float *)nout->data;
  in = (float *)nin->data;
  for (I=0; I<=N-1; I++) {

    tensor = in + I*7;
    if (tenAniso_Conf != aniso && tensor[0] < confThresh) {
      out[I] = 0.0;
      continue;
    }


    out[I] = tenAnisoTen_f(tensor, aniso);
    if (!AIR_EXISTS(out[I])) {
      size_t coord[3];
      NRRD_COORD_GEN(coord, size, 3, I);
      biffAddf(TEN, "%s: generated non-existent aniso %g from tensor "
               "(%g) %g %g %g   %g %g   %g at sample %u = (%u,%u,%u)", me,
               out[I],
               tensor[0], tensor[1], tensor[2], tensor[3],
               tensor[4], tensor[5], tensor[6],
               AIR_CAST(unsigned int, I),
               AIR_CAST(unsigned int, coord[0]),
               AIR_CAST(unsigned int, coord[1]),
               AIR_CAST(unsigned int, coord[2]));
      return 1;
    }
  }
  ELL_3V_SET(map, 1, 2, 3);
  if (nrrdAxisInfoCopy(nout, nin, map, NRRD_AXIS_INFO_SIZE_BIT)) {
    biffMovef(TEN, NRRD, "%s: trouble", me);
    return 1;
  }
  if (nrrdBasicInfoCopy(nout, nin,
                        NRRD_BASIC_INFO_ALL ^ NRRD_BASIC_INFO_SPACE)) {
    biffAddf(NRRD, "%s:", me);
    return 1;
  }

  return 0;
}
