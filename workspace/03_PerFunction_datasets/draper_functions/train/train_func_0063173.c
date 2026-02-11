drawImage(GfxState *state, Object *ref, Stream *str,
				int width, int height,
				GfxImageColorMap *colorMap,
				GBool interpolate, int *maskColors, GBool inlineImg)
{
  unsigned int *data;
  unsigned int *line;
  int x, y;
  ImageStream *imgStr;
  Guchar *pix;
  int i;
  double *ctm;
  QMatrix matrix;
  QImage image;
  int stride;


  imgStr = new ImageStream(str, width,
			   colorMap->getNumPixelComps(),
			   colorMap->getBits());
  imgStr->reset();

  image = QImage(width, height, QImage::Format_ARGB32);
  data = (unsigned int *)image.bits();
  stride = image.bytesPerLine()/4;
  for (y = 0; y < height; y++) {
    pix = imgStr->getLine();
    line = data+y*stride;
    colorMap->getRGBLine(pix, line, width);

    if (maskColors) {
      for (x = 0; x < width; x++) {
        for (i = 0; i < colorMap->getNumPixelComps(); ++i) {
            if (pix[i] < maskColors[2*i] * 255||
                pix[i] > maskColors[2*i+1] * 255) {
                *line = *line | 0xff000000;
                break;
            }
        }
        pix += colorMap->getNumPixelComps();
        line++;
      }
    } else {
      for (x = 0; x < width; x++) { *line = *line | 0xff000000; line++; }
    }
  }

  ctm = state->getCTM();
  matrix.setMatrix(ctm[0] / width, ctm[1] / width, -ctm[2] / height, -ctm[3] / height, ctm[2] + ctm[4], ctm[3] + ctm[5]);

  m_painter->setMatrix(matrix, true);
  m_painter->drawImage( QPoint(0,0), image );
  delete imgStr;

}
