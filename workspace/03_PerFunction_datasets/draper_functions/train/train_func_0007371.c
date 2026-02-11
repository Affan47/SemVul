drawImageMask(GfxState *state, Object *ref, Stream *str,
				    int width, int height, GBool invert,
				    GBool interpolate, GBool inlineImg) {
  double *ctm;
  SplashCoord mat[6];
  SplashOutImageMaskData imgMaskData;

  if (state->getFillColorSpace()->isNonMarking()) {
    return;
  }
  setOverprintMask(state->getFillColorSpace(), state->getFillOverprint(),
		   state->getOverprintMode(), state->getFillColor());

  ctm = state->getCTM();
  for (int i = 0; i < 6; ++i) {
    if (!isfinite(ctm[i])) return;
  }
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

  splash->fillImageMask(&imageMaskSrc, &imgMaskData, width, height, mat, t3GlyphStack != NULL);
  if (inlineImg) {
    if (inlineImg) {
      while (imgMaskData.y < height) {
        imgMaskData.imgStr->getLine();
        ++imgMaskData.y;
      }
    }
  }

  delete imgMaskData.imgStr;
  str->close();
}
