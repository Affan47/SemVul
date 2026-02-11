airFPClass_d(double val) {
  _airDoubleEndianLittle dlit;
  _airDoubleEndianBig dbig;
  unsigned int sign, expo, mant0, mant1;
  int indexv, ret=0;
  unsigned char hibit;

  dlit.v = dbig.v = val;


  FP_GET_D(sign, expo, mant0, mant1, dlit, dbig);
  hibit = AIR_CAST(unsigned char, mant0 >> 19);

  indexv = ((!!sign) << 2) | ((!!expo) << 1) | (!!mant0 || !!mant1);
  switch(indexv) {
  case 0:

    ret = airFP_POS_ZERO;
    break;
  case 1:

    ret = airFP_POS_DENORM;
    break;
  case 2:

    if (0x7ff > expo) {
      ret = airFP_POS_NORM;
    } else {
      ret = airFP_POS_INF;
    }
    break;
  case 3:

    if (0x7ff > expo) {
      ret = airFP_POS_NORM;
    } else {
      if (TEEM_QNANHIBIT == hibit) {
        ret = airFP_QNAN;
      } else {
        ret = airFP_SNAN;
      }
    }
    break;
  case 4:

    ret = airFP_NEG_ZERO;
    break;
  case 5:

    ret = airFP_NEG_DENORM;
    break;
  case 6:

    if (0x7ff > expo) {
      ret = airFP_NEG_NORM;
    } else {
      ret = airFP_NEG_INF;
    }
    break;
  case 7:

    if (0x7ff > expo)
      ret = airFP_NEG_NORM;
    else {
      if (TEEM_QNANHIBIT == hibit) {
        ret = airFP_QNAN;
      } else {
        ret = airFP_SNAN;
      }
    }
    break;
  }
  return ret;
}
