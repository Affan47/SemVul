make_color_buffer_mask(struct gl_context *ctx, GLint drawbuffer)
{
   const struct gl_renderbuffer_attachment *att = ctx->DrawBuffer->Attachment;
   GLbitfield mask = 0x0;


   if (drawbuffer < 0 || drawbuffer >= (GLint)ctx->Const.MaxDrawBuffers) {
      return INVALID_MASK;
   }

   switch (ctx->DrawBuffer->ColorDrawBuffer[drawbuffer]) {
   case GL_FRONT:
      if (att[BUFFER_FRONT_LEFT].Renderbuffer)
         mask |= BUFFER_BIT_FRONT_LEFT;
      if (att[BUFFER_FRONT_RIGHT].Renderbuffer)
         mask |= BUFFER_BIT_FRONT_RIGHT;
      break;
   case GL_BACK:
      if (att[BUFFER_BACK_LEFT].Renderbuffer)
         mask |= BUFFER_BIT_BACK_LEFT;
      if (att[BUFFER_BACK_RIGHT].Renderbuffer)
         mask |= BUFFER_BIT_BACK_RIGHT;
      break;
   case GL_LEFT:
      if (att[BUFFER_FRONT_LEFT].Renderbuffer)
         mask |= BUFFER_BIT_FRONT_LEFT;
      if (att[BUFFER_BACK_LEFT].Renderbuffer)
         mask |= BUFFER_BIT_BACK_LEFT;
      break;
   case GL_RIGHT:
      if (att[BUFFER_FRONT_RIGHT].Renderbuffer)
         mask |= BUFFER_BIT_FRONT_RIGHT;
      if (att[BUFFER_BACK_RIGHT].Renderbuffer)
         mask |= BUFFER_BIT_BACK_RIGHT;
      break;
   case GL_FRONT_AND_BACK:
      if (att[BUFFER_FRONT_LEFT].Renderbuffer)
         mask |= BUFFER_BIT_FRONT_LEFT;
      if (att[BUFFER_BACK_LEFT].Renderbuffer)
         mask |= BUFFER_BIT_BACK_LEFT;
      if (att[BUFFER_FRONT_RIGHT].Renderbuffer)
         mask |= BUFFER_BIT_FRONT_RIGHT;
      if (att[BUFFER_BACK_RIGHT].Renderbuffer)
         mask |= BUFFER_BIT_BACK_RIGHT;
      break;
   default:
      {
         GLint buf = ctx->DrawBuffer->_ColorDrawBufferIndexes[drawbuffer];

         if (buf >= 0 && att[buf].Renderbuffer) {
            mask |= 1 << buf;
         }
      }
   }

   return mask;
}
