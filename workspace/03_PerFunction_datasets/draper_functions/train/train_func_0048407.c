dri2InvalidateBuffers(Display *dpy, XID drawable)
{
   __GLXdisplayPrivate *priv = __glXInitialize(dpy);
   struct x11_screen *xscr = NULL;

   if (priv && priv->xscr)
      xscr = priv->xscr;
   if (!xscr || !xscr->dri_invalidate_buffers)
      return;

   xscr->dri_invalidate_buffers(xscr, drawable, xscr->dri_user_data);
}
