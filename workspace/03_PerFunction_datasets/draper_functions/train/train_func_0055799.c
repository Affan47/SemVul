dri3_flush(struct dri3_screen *psc,
           struct dri3_drawable *draw,
           unsigned flags,
           enum __DRI2throttleReason throttle_reason)
{
   struct glx_context *gc = __glXGetCurrentContext();

   if (gc) {
      struct dri3_context *dri3Ctx = (struct dri3_context *)gc;

      (*psc->f->flush_with_flags)(dri3Ctx->driContext, draw->driDrawable, flags, throttle_reason);
   }
}
