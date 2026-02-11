drawImageMask(GfxState *state, Object *ref, Stream *str,
				int width, int height, GBool invert,
				GBool interpolate, GBool inlineImg) {
  int len;

  len = height * ((width + 7) / 8);
  if (state->getFillColorSpace()->getMode() == csPattern && (level != psLevel1 && level != psLevel1Sep)) {
    maskToClippingPath(str, width, height, invert);
  } else {
    switch (level) {
      case psLevel1:
      case psLevel1Sep:
        doImageL1(ref, NULL, invert, inlineImg, str, width, height, len);
      break;
      case psLevel2:
      case psLevel2Sep:
        doImageL2(ref, NULL, invert, inlineImg, str, width, height, len,
                  NULL, NULL, 0, 0, gFalse);
      break;
      case psLevel3:
      case psLevel3Sep:
        doImageL3(ref, NULL, invert, inlineImg, str, width, height, len,
                  NULL, NULL, 0, 0, gFalse);
      break;
    }
  }
}
