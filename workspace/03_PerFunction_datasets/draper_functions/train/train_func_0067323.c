dri3_flush_front_buffer(__DRIdrawable *driDrawable, void *loaderPrivate)
{
   struct glx_context *gc;
   struct dri3_drawable *pdraw = loaderPrivate;
   struct dri3_screen *psc;

   if (!pdraw)
      return;

   if (!pdraw->base.psc)
      return;

   psc = (struct dri3_screen *) pdraw->base.psc;

   (void) __glXInitialize(psc->base.dpy);

   gc = __glXGetCurrentContext();

   dri3_flush(psc, pdraw, __DRI2_FLUSH_DRAWABLE, __DRI2_THROTTLE_FLUSHFRONT);

   dri3_wait_gl(gc);
}
