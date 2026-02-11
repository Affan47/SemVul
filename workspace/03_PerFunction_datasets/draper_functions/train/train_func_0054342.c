change_fiberlamp(ModeInfo * mi)
{
  fiberlampstruct *fl;
  if (fiberlamps == NULL)
	return;
  fl = &fiberlamps[MI_SCREEN(mi)];
  fl->cx = (DRAND(SCALE/4)-SCALE/8)/SCALE;
  fl->count = 0;
  if (fl->dbufp) {
    XSetForeground(MI_DISPLAY(mi), MI_GC(mi), MI_BLACK_PIXEL(mi));
    XFillRectangle(MI_DISPLAY(mi), fl->buffer, MI_GC(mi), 0, 0,
                   MI_WIDTH(mi), MI_HEIGHT(mi));
  }
}
