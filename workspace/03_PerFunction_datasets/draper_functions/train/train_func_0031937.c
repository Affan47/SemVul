_mesa_detach_renderbuffer(struct gl_context *ctx,
                          struct gl_framebuffer *fb,
                          const void *att)
{
   unsigned i;
   bool progress = false;

   for (i = 0; i < BUFFER_COUNT; i++) {
      if (fb->Attachment[i].Texture == att
          || fb->Attachment[i].Renderbuffer == att) {
         remove_attachment(ctx, &fb->Attachment[i]);
         progress = true;
      }
   }


   if (progress)
      invalidate_framebuffer(fb);

   return progress;
}
