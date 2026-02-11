unbind_texobj_from_fbo(struct gl_context *ctx,
                       struct gl_texture_object *texObj)
{
   bool progress = false;


   if (_mesa_is_user_fbo(ctx->DrawBuffer)) {
      progress = _mesa_detach_renderbuffer(ctx, ctx->DrawBuffer, texObj);
   }
   if (_mesa_is_user_fbo(ctx->ReadBuffer)
       && ctx->ReadBuffer != ctx->DrawBuffer) {
      progress = _mesa_detach_renderbuffer(ctx, ctx->ReadBuffer, texObj)
         || progress;
   }

   if (progress)

      ctx->NewState |= _NEW_BUFFERS;
}
