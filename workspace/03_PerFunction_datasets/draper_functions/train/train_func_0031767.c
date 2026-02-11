DestroyDrawable(Display * dpy, GLXDrawable drawable, CARD32 glxCode)
{
   if ((dpy == NULL) || (drawable == 0)) {
      return;
   }

   protocolDestroyDrawable(dpy, drawable, glxCode);

   DestroyGLXDrawable(dpy, drawable);
   DestroyDRIDrawable(dpy, drawable, GL_FALSE);

   return;
}
