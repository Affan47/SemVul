DestroyPbuffer(Display * dpy, GLXDrawable drawable)
{
   struct glx_display *priv = __glXInitialize(dpy);
   CARD8 opcode;

   if ((dpy == NULL) || (drawable == 0)) {
      return;
   }

   opcode = __glXSetupForCommand(dpy);
   if (!opcode)
      return;

   LockDisplay(dpy);

   if ((priv->majorVersion > 1) || (priv->minorVersion >= 3)) {
      xGLXDestroyPbufferReq *req;

      GetReq(GLXDestroyPbuffer, req);
      req->reqType = opcode;
      req->glxCode = X_GLXDestroyPbuffer;
      req->pbuffer = (GLXPbuffer) drawable;
   }
   else {
      xGLXVendorPrivateWithReplyReq *vpreq;
      CARD32 *data;

      GetReqExtra(GLXVendorPrivateWithReply, 4, vpreq);
      data = (CARD32 *) (vpreq + 1);

      data[0] = (CARD32) drawable;

      vpreq->reqType = opcode;
      vpreq->glxCode = X_GLXVendorPrivateWithReply;
      vpreq->vendorCode = X_GLXvop_DestroyGLXPbufferSGIX;
   }

   UnlockDisplay(dpy);
   SyncHandle();

   DestroyDRIDrawable(dpy, drawable, GL_TRUE);

   return;
}
