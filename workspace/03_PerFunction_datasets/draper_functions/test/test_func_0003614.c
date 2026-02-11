setSoftMaskFromImageMask(GfxState *state,
					       Object *ref, Stream *str,
					       int width, int height,
					       GBool invert,
					       GBool inlineImg, double *baseMatrix) {
  double *ctm;
  SplashCoord mat[6];
  SplashOutImageMaskData imgMaskData;
  Splash *maskSplash;
  SplashColor maskColor;
  double bbox[4] = {0, 0, 1, 1};

  if (state->getFillColorSpace()->isNonMarking()) {
    return;
  }

  ctm = state->getCTM();
  for (int i = 0; i < 6; ++i) {
    if (!isfinite(ctm[i])) return;
  }

  beginTransparencyGroup(state, bbox, NULL, gFalse, gFalse, gFalse);
  baseMatrix[4] -= transpGroupStack->tx;
  baseMatrix[5] -= transpGroupStack->ty;

  ctm = state->getCTM();
  mat[0] = ctm[0];
  mat[1] = ctm[1];
  mat[2] = -ctm[2];
  mat[3] = -ctm[3];
  mat[4] = ctm[2] + ctm[4];
  mat[5] = ctm[3] + ctm[5];
  imgMaskData.imgStr = new ImageStream(str, width, 1, 1);
  imgMaskData.imgStr->reset();
  imgMaskData.invert = invert ? 0 : 1;
  imgMaskData.width = width;
  imgMaskData.height = height;
  imgMaskData.y = 0;

  maskBitmap = new SplashBitmap(bitmap->getWidth(), bitmap->getHeight(), 1, splashModeMono8, gFalse);
  maskSplash = new Splash(maskBitmap, vectorAntialias);
  maskColor[0] = 0;
  maskSplash->clear(maskColor);
  maskColor[0] = 0xff;
  maskSplash->setFillPattern(new SplashSolidColor(maskColor));
  maskSplash->fillImageMask(&imageMaskSrc, &imgMaskData,  width, height, mat, t3GlyphStack != NULL);
  delete maskSplash;
  delete imgMaskData.imgStr;
  str->close();
}
