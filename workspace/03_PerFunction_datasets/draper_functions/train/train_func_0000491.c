graphicsToDeviceCoordinates(const JsGraphics *gfx, short *x, short *y) {
  if (gfx->data.flags & JSGRAPHICSFLAGS_SWAP_XY) {
    short t = *x;
    *x = *y;
    *y = t;
  }
  if (gfx->data.flags & JSGRAPHICSFLAGS_INVERT_X) *x = (short)(gfx->data.width - (*x+1));
  if (gfx->data.flags & JSGRAPHICSFLAGS_INVERT_Y) *y = (short)(gfx->data.height - (*y+1));
}
