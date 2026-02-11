_mesa_update_draw_buffer_bounds(struct gl_context *ctx)
{
   struct gl_framebuffer *buffer = ctx->DrawBuffer;
   int bbox[4];

   if (!buffer)
      return;

   if (_mesa_is_user_fbo(buffer)) {

      update_framebuffer_size(ctx, buffer);
   }


   _mesa_scissor_bounding_box(ctx, buffer, 0, bbox);
   buffer->_Xmin = bbox[0];
   buffer->_Ymin = bbox[2];
   buffer->_Xmax = bbox[1];
   buffer->_Ymax = bbox[3];
}
