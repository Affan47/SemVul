Redisplay(Widget w, XEvent *event, Region region)
{
  XExposeEvent *exposeEvent = (XExposeEvent *)event;
  CanvasWidget	cw = (CanvasWidget)w;

  if (!XtIsRealized(w))
    return;

  if(cw->canvas.redraw) {
    (cw->canvas.redraw)((Widget)cw,exposeEvent,region,cw->canvas.redraw_data);
  }
  else {
    if(cw->canvas.is_visible)
      XCopyArea(display, cw->canvas.pixmap, XtWindow(w),
		civ_gc,
		0, 0,
		cw->core.width, cw->core.height,
		0, 0);
    else {
      XSetForeground(display, fill_bg_gc, cw->core.background_pixel);
      XFillRectangle(display, XtWindow(w), fill_bg_gc,
		     0, 0, cw->core.width, cw->core.height);
    }
  }
}
