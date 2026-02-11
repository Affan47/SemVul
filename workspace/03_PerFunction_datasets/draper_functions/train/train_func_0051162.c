intelCopyTexSubImage(struct gl_context *ctx, GLuint dims,
                     struct gl_texture_image *texImage,
                     GLint xoffset, GLint yoffset, GLint slice,
                     struct gl_renderbuffer *rb,
                     GLint x, GLint y,
                     GLsizei width, GLsizei height)
{
   struct intel_context *intel = intel_context(ctx);


   if (intel_copy_texsubimage(intel,
                              intel_texture_image(texImage),
                              xoffset, yoffset, slice,
                              intel_renderbuffer(rb), x, y, width, height)) {
      return;
   }


   perf_debug("%s - fallback to swrast\n", __FUNCTION__);
   _mesa_meta_CopyTexSubImage(ctx, dims, texImage,
                              xoffset, yoffset, slice,
                              rb, x, y, width, height);
}
