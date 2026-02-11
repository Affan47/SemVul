fast_draw_rgba_pixels(struct gl_context *ctx, GLint x, GLint y,
                      GLsizei width, GLsizei height,
                      GLenum format, GLenum type,
                      const struct gl_pixelstore_attrib *userUnpack,
                      const GLvoid *pixels)
{
   struct gl_renderbuffer *rb = ctx->DrawBuffer->_ColorDrawBuffers[0];
   SWcontext *swrast = SWRAST_CONTEXT(ctx);
   struct gl_pixelstore_attrib unpack;

   if (!rb)
      return GL_TRUE;

   if (ctx->DrawBuffer->_NumColorDrawBuffers > 1 ||
       (swrast->_RasterMask & ~CLIP_BIT) ||
       ctx->Texture._EnabledCoordUnits ||
       userUnpack->SwapBytes ||
       ctx->Pixel.ZoomX != 1.0f ||
       fabsf(ctx->Pixel.ZoomY) != 1.0f ||
       ctx->_ImageTransferState) {

      return GL_FALSE;
   }

   unpack = *userUnpack;


   if (!_mesa_clip_drawpixels(ctx, &x, &y, &width, &height, &unpack)) {

      return GL_TRUE;
   }

   if (format == GL_RGB &&
       type == GL_UNSIGNED_BYTE &&
       (rb->Format == MESA_FORMAT_B8G8R8X8_UNORM ||
        rb->Format == MESA_FORMAT_B8G8R8A8_UNORM)) {
      fast_draw_rgb_ubyte_pixels(ctx, rb, x, y, width, height,
                                 &unpack, pixels);
      return GL_TRUE;
   }

   if (format == GL_RGBA &&
       type == GL_UNSIGNED_BYTE &&
       (rb->Format == MESA_FORMAT_B8G8R8X8_UNORM ||
        rb->Format == MESA_FORMAT_B8G8R8A8_UNORM)) {
      fast_draw_rgba_ubyte_pixels(ctx, rb, x, y, width, height,
                                  &unpack, pixels);
      return GL_TRUE;
   }

   if (_mesa_format_matches_format_and_type(rb->Format, format, type,
                                            ctx->Unpack.SwapBytes)) {
      fast_draw_generic_pixels(ctx, rb, x, y, width, height,
                               format, type, &unpack, pixels);
      return GL_TRUE;
   }


   return GL_FALSE;
}
