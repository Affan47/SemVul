update_color_read_buffer(struct gl_context *ctx, struct gl_framebuffer *fb)
{
   (void) ctx;
   if (fb->_ColorReadBufferIndex == -1 ||
       fb->DeletePending ||
       fb->Width == 0 ||
       fb->Height == 0) {
      fb->_ColorReadBuffer = NULL;
   }
   else {
      ASSERT(fb->_ColorReadBufferIndex >= 0);
      ASSERT(fb->_ColorReadBufferIndex < BUFFER_COUNT);
      fb->_ColorReadBuffer
         = fb->Attachment[fb->_ColorReadBufferIndex].Renderbuffer;
   }
}
