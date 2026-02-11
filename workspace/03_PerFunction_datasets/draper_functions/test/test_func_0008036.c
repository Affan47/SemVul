glXCopyContext(Display * dpy, GLXContext source_user,
	       GLXContext dest_user, unsigned long mask)
{
   struct glx_context *source = (struct glx_context *) source_user;
   struct glx_context *dest = (struct glx_context *) dest_user;
#ifdef GLX_USE_APPLEGL
   struct glx_context *gc = __glXGetCurrentContext();
   int errorcode;
   bool x11error;

   if(apple_glx_copy_context(gc->driContext, source->driContext, dest->driContext,
                             mask, &errorcode, &x11error)) {
      __glXSendError(dpy, errorcode, 0, X_GLXCopyContext, x11error);
   }

#else
   xGLXCopyContextReq *req;
   struct glx_context *gc = __glXGetCurrentContext();
   GLXContextTag tag;
   CARD8 opcode;

   opcode = __glXSetupForCommand(dpy);
   if (!opcode) {
      return;
   }

#if defined(GLX_DIRECT_RENDERING) && !defined(GLX_USE_APPLEGL)
   if (gc->isDirect) {

   }
#endif


   if (source == gc && dpy == gc->currentDpy) {
      tag = gc->currentContextTag;
   }
   else {
      tag = 0;
   }


   LockDisplay(dpy);
   GetReq(GLXCopyContext, req);
   req->reqType = opcode;
   req->glxCode = X_GLXCopyContext;
   req->source = source ? source->xid : None;
   req->dest = dest ? dest->xid : None;
   req->mask = mask;
   req->contextTag = tag;
   UnlockDisplay(dpy);
   SyncHandle();
#endif
}
