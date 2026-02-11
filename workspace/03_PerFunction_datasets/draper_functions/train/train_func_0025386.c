draw_rgba_pixels( struct gl_context *ctx, GLint x, GLint y,
                  GLsizei width, GLsizei height,
                  GLenum format, GLenum type,
                  const struct gl_pixelstore_attrib *unpack,
                  const GLvoid *pixels )
{
   const GLint imgX = x, imgY = y;
   const GLboolean zoom = ctx->Pixel.ZoomX!=1.0 || ctx->Pixel.ZoomY!=1.0;
   GLfloat *convImage = NULL;
   GLbitfield transferOps = ctx->_ImageTransferState;
   SWspan span;


   if (fast_draw_rgba_pixels(ctx, x, y, width, height, format, type,
                             unpack, pixels)) {
      return;
   }

   swrast_render_start(ctx);

   INIT_SPAN(span, GL_BITMAP);
   _swrast_span_default_attribs(ctx, &span);
   span.arrayMask = SPAN_RGBA;
   span.arrayAttribs = VARYING_BIT_COL0;

   if (ctx->DrawBuffer->_NumColorDrawBuffers > 0) {
      GLenum datatype = _mesa_get_format_datatype(
                 ctx->DrawBuffer->_ColorDrawBuffers[0]->Format);
      if (datatype != GL_FLOAT &&
          ctx->Color.ClampFragmentColor != GL_FALSE) {

         transferOps |= IMAGE_CLAMP_BIT;
      }
   }


   {
      const GLbitfield interpMask = span.interpMask;
      const GLbitfield arrayMask = span.arrayMask;
      const GLint srcStride
         = _mesa_image_row_stride(unpack, width, format, type);
      GLint skipPixels = 0;

      GLfloat *rgba = (GLfloat *) span.array->attribs[VARYING_SLOT_COL0];


      while (skipPixels < width) {
         const GLint spanWidth = MIN2(width - skipPixels, SWRAST_MAX_WIDTH);
         const GLubyte *source
            = (const GLubyte *) _mesa_image_address2d(unpack, pixels,
                                                      width, height, format,
                                                      type, 0, skipPixels);
         GLint row;

         for (row = 0; row < height; row++) {

            _mesa_unpack_color_span_float(ctx, spanWidth, GL_RGBA, rgba,
                                     format, type, source, unpack,
                                     transferOps);


	    span.array->ChanType = GL_FLOAT;
	    span.x = x + skipPixels;
	    span.y = y + row;
	    span.end = spanWidth;
	    span.arrayMask = arrayMask;
	    span.interpMask = interpMask;
	    if (zoom) {
	       _swrast_write_zoomed_rgba_span(ctx, imgX, imgY, &span, rgba);
	    }
	    else {
	       _swrast_write_rgba_span(ctx, &span);
	    }

            source += srcStride;
         }

         skipPixels += spanWidth;
      }


      span.array->ChanType = CHAN_TYPE;
   }

   free(convImage);

   swrast_render_finish(ctx);
}
