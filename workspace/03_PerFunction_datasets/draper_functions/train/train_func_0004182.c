__glXReportDamage(__DRIdrawable * driDraw,
                  int x, int y,
                  drm_clip_rect_t * rects, int num_rects,
                  GLboolean front_buffer, void *loaderPrivate)
{
   XRectangle *xrects;
   XserverRegion region;
   int i;
   int x_off, y_off;
   __GLXDRIdrawable *glxDraw = loaderPrivate;
   struct glx_screen *psc = glxDraw->psc;
   Display *dpy = psc->dpy;
   Drawable drawable;

   if (!has_damage_post(dpy))
      return;

   if (front_buffer) {
      x_off = x;
      y_off = y;
      drawable = RootWindow(dpy, psc->scr);
   }
   else {
      x_off = 0;
      y_off = 0;
      drawable = glxDraw->xDrawable;
   }

   xrects = malloc(sizeof(XRectangle) * num_rects);
   if (xrects == NULL)
      return;

   for (i = 0; i < num_rects; i++) {
      xrects[i].x = rects[i].x1 + x_off;
      xrects[i].y = rects[i].y1 + y_off;
      xrects[i].width = rects[i].x2 - rects[i].x1;
      xrects[i].height = rects[i].y2 - rects[i].y1;
   }
   region = XFixesCreateRegion(dpy, xrects, num_rects);
   free(xrects);
   XDamageAdd(dpy, drawable, region);
   XFixesDestroyRegion(dpy, region);
}
