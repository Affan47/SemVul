_mesa_ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value)
{
   GET_CURRENT_CONTEXT(ctx);

   FLUSH_VERTICES(ctx, 0);
   FLUSH_CURRENT(ctx, 0);

   if (ctx->NewState) {
      _mesa_update_state( ctx );
   }

   switch (buffer) {
   case GL_COLOR:
      {
         const GLbitfield mask = make_color_buffer_mask(ctx, drawbuffer);
         if (mask == INVALID_MASK) {
            _mesa_error(ctx, GL_INVALID_VALUE, "glClearBufferuiv(drawbuffer=%d)",
                        drawbuffer);
            return;
         }
         else if (mask && !ctx->RasterDiscard) {
            union gl_color_union clearSave;


            clearSave = ctx->Color.ClearColor;

            COPY_4V(ctx->Color.ClearColor.ui, value);

            ctx->Driver.Clear(ctx, mask);

            ctx->Color.ClearColor = clearSave;
         }
      }
      break;
   case GL_DEPTH:
   case GL_STENCIL:


      if (drawbuffer != 0) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glClearBufferuiv(drawbuffer=%d)",
                     drawbuffer);
         return;
      }
      return;
   default:
      _mesa_error(ctx, GL_INVALID_ENUM, "glClearBufferuiv(buffer=%s)",
                  _mesa_lookup_enum_by_nr(buffer));
      return;
   }
}
