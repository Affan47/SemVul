validate_pbo_access(struct gl_context *ctx,
                    struct gl_pixelstore_attrib *pack, GLsizei mapsize,
                    GLenum format, GLenum type, GLsizei clientMemSize,
                    const GLvoid *ptr)
{
   GLboolean ok;


   _mesa_reference_buffer_object(ctx,
                                 &ctx->DefaultPacking.BufferObj,
                                 pack->BufferObj);

   ok = _mesa_validate_pbo_access(1, &ctx->DefaultPacking, mapsize, 1, 1,
                                  format, type, clientMemSize, ptr);


   _mesa_reference_buffer_object(ctx,
                                 &ctx->DefaultPacking.BufferObj,
                                 ctx->Shared->NullBufferObj);

   if (!ok) {
      if (_mesa_is_bufferobj(pack->BufferObj)) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "gl[Get]PixelMap*v(out of bounds PBO access)");
      } else {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetnPixelMap*vARB(out of bounds access:"
                     " bufSize (%d) is too small)", clientMemSize);
      }
   }
   return ok;
}
