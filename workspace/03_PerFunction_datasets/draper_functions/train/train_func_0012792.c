__glXSwapBuffersMscOML(Display * dpy, GLXDrawable drawable,
                       int64_t target_msc, int64_t divisor, int64_t remainder)
{
   struct glx_context *gc = __glXGetCurrentContext();
#ifdef GLX_DIRECT_RENDERING
   __GLXDRIdrawable *pdraw = GetGLXDRIDrawable(dpy, drawable);
   struct glx_screen *psc = pdraw ? pdraw->psc : NULL;
#endif

   if (!gc)
      return -1;

#ifdef GLX_DIRECT_RENDERING
   if (!pdraw || !gc->isDirect)
      return -1;
#endif


   if (divisor < 0 || remainder < 0 || target_msc < 0)
      return -1;
   if (divisor > 0 && remainder >= divisor)
      return -1;

   if (target_msc == 0 && divisor == 0 && remainder == 0)
      remainder = 1;

#ifdef GLX_DIRECT_RENDERING
   if (psc->driScreen && psc->driScreen->swapBuffers)
      return (*psc->driScreen->swapBuffers)(pdraw, target_msc, divisor,
					    remainder, False);
#endif

   return -1;
}
