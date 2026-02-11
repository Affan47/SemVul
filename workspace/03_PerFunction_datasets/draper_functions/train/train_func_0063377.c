getRGBLine(int yl, SplashColorPtr line) {
  SplashColor col;
  double c, m, y, k, c1, m1, y1, k1, r, g, b;

  for (int x = 0; x < width; x++) {
    getPixel(x, yl, col);
    c = byteToDbl(col[0]);
    m = byteToDbl(col[1]);
    y = byteToDbl(col[2]);
    k = byteToDbl(col[3]);
#if SPLASH_CMYK
    if (separationList->getLength() > 0) {
      for (int i = 0; i < separationList->getLength(); i++) {
        if (col[i+4] > 0) {
          GfxCMYK cmyk;
          GfxColor input;
          input.c[0] = byteToCol(col[i+4]);
          GfxSeparationColorSpace *sepCS = (GfxSeparationColorSpace *)separationList->get(i);
          sepCS->getCMYK(&input, &cmyk);
          col[0] = colToByte(cmyk.c);
          col[1] = colToByte(cmyk.m);
          col[2] = colToByte(cmyk.y);
          col[3] = colToByte(cmyk.k);
          c += byteToDbl(col[0]);
          m += byteToDbl(col[1]);
          y += byteToDbl(col[2]);
          k += byteToDbl(col[3]);
        }
      }
      if (c > 1) c = 1;
      if (m > 1) m = 1;
      if (y > 1) y = 1;
      if (k > 1) k = 1;
    }
#endif
    c1 = 1 - c;
    m1 = 1 - m;
    y1 = 1 - y;
    k1 = 1 - k;
    cmykToRGBMatrixMultiplication(c, m, y, k, c1, m1, y1, k1, r, g, b);
    *line++ = dblToByte(clip01(r));
    *line++ = dblToByte(clip01(g));
    *line++ = dblToByte(clip01(b));
  }
}
