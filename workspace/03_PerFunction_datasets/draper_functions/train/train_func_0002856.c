parmConvert(double *parmDst, const double *parmSrc,
            const tenModel *modelSrc) {
  int ret;

  if (modelSrc == tenModelBall) {
    TEN_T_SET(parmDst, parmSrc[0],
              parmSrc[1], 0, 0,
              parmSrc[1], 0,
              parmSrc[1]);
    ret = 0;
  } else if (modelSrc == tenModel1Stick) {
    double ten[7];
    TEN_T3V_OUTER(ten, parmSrc + 2);
    TEN_T_SCALE(parmDst, parmSrc[1], ten);
    parmDst[0] = parmSrc[0];
    ret = 0;
  } else if (modelSrc == tenModelBall1Stick) {
    double stick[7], ball[7], diff, frac;
    diff = parmSrc[1];
    frac = parmSrc[2];
    TEN_T3V_OUTER(stick, parmSrc + 3);
    TEN_T_SCALE(stick, diff, stick);
    TEN_T_SET(ball, 1, diff, 0, 0, diff, 0, diff);
    TEN_T_LERP(parmDst, frac, ball, stick);
    parmDst[0] = parmSrc[0];
    ret = 1;
  } else if (modelSrc == tenModel1Cylinder) {
    double stick[7], ball[7], len, rad;
    len = parmSrc[1];
    rad = parmSrc[2];
    TEN_T3V_OUTER(stick, parmSrc + 3);
    TEN_T_SCALE(stick, len-rad, stick);
    TEN_T_SET(ball, 1, rad, 0, 0, rad, 0, rad);
    TEN_T_ADD(parmDst, ball, stick);
    parmDst[0] = parmSrc[0];
    ret = 0;
  } else if (modelSrc == tenModel1Tensor2) {
    parmCopy(parmDst, parmSrc);
    ret = 0;
  } else {
    unsigned int ii;
    for (ii=0; ii<PARM_NUM; ii++) {
      parmDst[ii] = AIR_NAN;
    }
    ret = 2;
  }
  return ret;
}
