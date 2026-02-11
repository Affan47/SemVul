AlphaRectangle(PRectangle rc, int cornerSize, ColourAllocated fill, int alphaFill,
    ColourAllocated outline, int alphaOutline, int flags) {
  if (dc()) {
    int width = rc.Width();
    int height = rc.Height();

    cornerSize = Platform::Minimum(cornerSize, (Platform::Minimum(width, height) / 2) - 2);

    FXImage * image = new FXImage(FXApp::instance(), NULL, IMAGE_OWNED, width, height);

    FXColor valEmpty = 0;
    FXColor valFill = FXRGBA(GetRed(fill.AsLong()), GetGreen(fill.AsLong()), GetBlue(fill.AsLong()), alphaFill);
    FXColor valOutline = FXRGBA(GetRed(outline.AsLong()), GetGreen(outline.AsLong()), GetBlue(outline.AsLong()), alphaOutline);
    for (int pY=0; pY<height; pY++) {
      for (int pX=0; pX<width; pX++) {
        if ((pX==0) || (pX==width-1) || (pY == 0) || (pY == height-1)) {
          image->setPixel(pX, pY, valOutline);
        } else {
          image->setPixel(pX, pY, valFill);
        }
      }
    }
    for (int c=0;c<cornerSize; c++) {
      for (int pX=0;pX<c+1; pX++) {
        AllFour(image, width, height, pX, c-pX, valEmpty);
      }
    }
    for (int pX=1;pX<cornerSize; pX++) {
      AllFour(image, width, height, pX, cornerSize-pX, valOutline);
    }


    image->create();
    _dc->drawImage(image, rc.left, rc.top);
  }
}
