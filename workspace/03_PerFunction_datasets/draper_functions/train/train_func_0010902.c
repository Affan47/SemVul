radeon_create_image_from_renderbuffer(__DRIcontext *context,
                                      int renderbuffer, void *loaderPrivate)
{
   __DRIimage *image;
   radeonContextPtr radeon = context->driverPrivate;
   struct gl_renderbuffer *rb;
   struct radeon_renderbuffer *rrb;

   rb = _mesa_lookup_renderbuffer(&radeon->glCtx, renderbuffer);
   if (!rb) {
      _mesa_error(&radeon->glCtx,
                  GL_INVALID_OPERATION, "glRenderbufferExternalMESA");
      return NULL;
   }

   rrb = radeon_renderbuffer(rb);
   image = calloc(1, sizeof *image);
   if (image == NULL)
      return NULL;

   image->internal_format = rb->InternalFormat;
   image->format = rb->Format;
   image->cpp = rrb->cpp;
   image->data_type = GL_UNSIGNED_BYTE;
   image->data = loaderPrivate;
   radeon_bo_ref(rrb->bo);
   image->bo = rrb->bo;

   image->width = rb->Width;
   image->height = rb->Height;
   image->pitch = rrb->pitch / image->cpp;

   return image;
}
