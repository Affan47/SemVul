limnPolyDataPlane(limnPolyData *pld,
                  unsigned int infoBitFlag,
                  unsigned int uRes, unsigned int vRes) {
  static const char me[]="limnPolyDataPlane";
  unsigned int vertNum, indxNum, primNum, uIdx, vIdx, vertIdx, primIdx;
  float uu, vv;


  uRes = AIR_MAX(2, uRes);
  vRes = AIR_MAX(2, vRes);

  vertNum = uRes*vRes;
  primNum = vRes-1;
  indxNum = primNum*2*uRes;
  if (limnPolyDataAlloc(pld, infoBitFlag, vertNum, indxNum, primNum)) {
    biffAddf(LIMN, "%s: couldn't allocate output", me);
    return 1;
  }

  vertIdx = 0;
  for (vIdx=0; vIdx<vRes; vIdx++) {
    vv = AIR_CAST(float, AIR_AFFINE(0, vIdx, vRes-1, -1.0, 1.0));
    for (uIdx=0; uIdx<uRes; uIdx++) {
      uu = AIR_CAST(float, AIR_AFFINE(0, uIdx, uRes-1, -1.0, 1.0));
      ELL_4V_SET(pld->xyzw + 4*vertIdx, uu, vv, 0.0, 1.0);
      if ((1 << limnPolyDataInfoNorm) & infoBitFlag) {
        ELL_3V_SET_TT(pld->norm + 3*vertIdx, float, 0.0, 0.0, 1.0);
      }
      if ((1 << limnPolyDataInfoRGBA) & infoBitFlag) {
        ELL_4V_SET(pld->rgba + 4*vertIdx, 255, 255, 255, 255);
      }
      if ((1 << limnPolyDataInfoTex2) & infoBitFlag) {
        ELL_2V_SET_TT(pld->tex2 + 2*vertIdx, float, (uu+1.0)/2.0, (vv+1.0)/2.0);
      }
      if ((1 << limnPolyDataInfoTang) & infoBitFlag) {
        ELL_3V_SET_TT(pld->tang + 3*vertIdx, float, 1.0, 0.0, 0.0);
      }
      ++vertIdx;
    }
  }

  vertIdx = 0;
  for (primIdx=0; primIdx<primNum; primIdx++) {
    for (uIdx=0; uIdx<uRes; uIdx++) {
      pld->indx[vertIdx++] = uIdx + uRes*(primIdx+1);
      pld->indx[vertIdx++] = uIdx + uRes*(primIdx);
    }
    pld->type[primIdx] = limnPrimitiveTriangleStrip;
    pld->icnt[primIdx] = 2*uRes;
  }

  return 0;
}
