unpack_image(struct gl_context *ctx, GLuint dimensions,
             GLsizei width, GLsizei height, GLsizei depth,
             GLenum format, GLenum type, const GLvoid * pixels,
             const struct gl_pixelstore_attrib *unpack)
{
   if (width <= 0 || height <= 0) {
      return NULL;
   }

   if (_mesa_bytes_per_pixel(format, type) < 0) {

      return NULL;
   }

   if (!_mesa_is_bufferobj(unpack->BufferObj)) {

      GLvoid *image;

      if (type == GL_BITMAP)
         image = _mesa_unpack_bitmap(width, height, pixels, unpack);
      else
         image = _mesa_unpack_image(dimensions, width, height, depth,
                                    format, type, pixels, unpack);
      if (pixels && !image) {
         _mesa_error(ctx, GL_OUT_OF_MEMORY, "display list construction");
      }
      return image;
   }
   else if (_mesa_validate_pbo_access(dimensions, unpack, width, height,
                                      depth, format, type, INT_MAX, pixels)) {
      const GLubyte *map, *src;
      GLvoid *image;

      map = (GLubyte *)
         ctx->Driver.MapBufferRange(ctx, 0, unpack->BufferObj->Size,
				    GL_MAP_READ_BIT, unpack->BufferObj);
      if (!map) {

         _mesa_error(ctx, GL_INVALID_OPERATION, "unable to map PBO");
         return NULL;
      }

      src = ADD_POINTERS(map, pixels);
      if (type == GL_BITMAP)
         image = _mesa_unpack_bitmap(width, height, src, unpack);
      else
         image = _mesa_unpack_image(dimensions, width, height, depth,
                                    format, type, src, unpack);

      ctx->Driver.UnmapBuffer(ctx, unpack->BufferObj);

      if (!image) {
         _mesa_error(ctx, GL_OUT_OF_MEMORY, "display list construction");
      }
      return image;
   }


   _mesa_error(ctx, GL_INVALID_OPERATION, "invalid PBO access");
   return NULL;
}
