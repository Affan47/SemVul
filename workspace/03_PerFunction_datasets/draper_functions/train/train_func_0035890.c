_swrast_depth_bounds_test( struct gl_context *ctx, SWspan *span )
{
   struct gl_framebuffer *fb = ctx->DrawBuffer;
   struct gl_renderbuffer *rb = fb->Attachment[BUFFER_DEPTH].Renderbuffer;
   GLubyte *zStart;
   GLuint zMin = (GLuint) (ctx->Depth.BoundsMin * fb->_DepthMaxF + 0.5F);
   GLuint zMax = (GLuint) (ctx->Depth.BoundsMax * fb->_DepthMaxF + 0.5F);
   GLubyte *mask = span->array->mask;
   const GLuint count = span->end;
   GLuint i;
   GLboolean anyPass = GL_FALSE;
   GLuint *zBufferTemp;
   const GLuint *zBufferVals;

   zBufferTemp = malloc(count * sizeof(GLuint));
   if (!zBufferTemp) {

      return GL_FALSE;
   }

   if (span->arrayMask & SPAN_XY)
      zStart = NULL;
   else
      zStart = _swrast_pixel_address(rb, span->x, span->y);

   if (rb->Format == MESA_FORMAT_Z_UNORM32 && !(span->arrayMask & SPAN_XY)) {

      zBufferVals = (const GLuint *) zStart;
   }
   else {

      if (span->arrayMask & SPAN_XY) {
         get_z32_values(ctx, rb, count, span->array->x, span->array->y,
                        zBufferTemp);
      }
      else {
         _mesa_unpack_uint_z_row(rb->Format, count, zStart, zBufferTemp);
      }
      zBufferVals = zBufferTemp;
   }


   for (i = 0; i < count; i++) {
      if (mask[i]) {
         if (zBufferVals[i] < zMin || zBufferVals[i] > zMax)
            mask[i] = GL_FALSE;
         else
            anyPass = GL_TRUE;
      }
   }

   free(zBufferTemp);

   return anyPass;
}
