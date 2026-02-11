glXGetCurrentDisplay(void)
{
   struct glx_context *gc = __glXGetCurrentContext();
   if (NULL == gc)
      return NULL;
   return gc->currentDpy;
}
