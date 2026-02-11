drawFormFieldButton(GfxResources *resources, GooString *da) {
  GooString *caption = NULL;
  if (appearCharacs)
    caption = appearCharacs->getNormalCaption();

  switch (static_cast<FormFieldButton *>(field)->getButtonType()) {
  case formButtonRadio: {

    if (appearState && appearState->cmp("Off") != 0) {
      if (caption) {
        drawText(caption, da, resources, gFalse, 0, fieldQuadCenter,
                 gFalse, gTrue);
      } else if (appearCharacs) {
        AnnotColor *aColor = appearCharacs->getBorderColor();
        if (aColor) {
          double dx = rect->x2 - rect->x1;
          double dy = rect->y2 - rect->y1;
          setColor(aColor, gTrue);
          drawCircle(0.5 * dx, 0.5 * dy, 0.2 * (dx < dy ? dx : dy), gTrue);
        }
      }
    }
  }
    break;
  case formButtonPush:
    if (caption)
      drawText(caption, da, resources, gFalse, 0, fieldQuadCenter, gFalse, gFalse);
    break;
  case formButtonCheck:
    if (appearState && appearState->cmp("Off") != 0) {
      if (!caption) {
        GooString checkMark("3");
        drawText(&checkMark, da, resources, gFalse, 0, fieldQuadCenter, gFalse, gTrue);
      } else {
        drawText(caption, da, resources, gFalse, 0, fieldQuadCenter, gFalse, gTrue);
      }
    }
    break;
  }
}
