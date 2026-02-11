DRI2EventToWire(Display *dpy, XEvent *event, xEvent *wire)
{
   XExtDisplayInfo *info = DRI2FindDisplay(dpy);
   DRI2Display *dri2dpy = dpy2dri(dpy);

   XextCheckExtension(dpy, info, dri2ExtensionName, False);

   if (dri2dpy && dri2dpy->ops && dri2dpy->ops->EventToWire) {
	   return dri2dpy->ops->EventToWire(dpy, info, event, wire);
   }

   return Success;
}
