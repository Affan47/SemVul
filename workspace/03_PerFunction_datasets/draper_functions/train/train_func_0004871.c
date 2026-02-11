_mesa_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params)
{
   struct gl_texture_object *texObj;
   GET_CURRENT_CONTEXT(ctx);

   texObj = get_texobj(ctx, target, GL_TRUE);
   if (!texObj)
      return;

   switch (pname) {
   case GL_TEXTURE_BORDER_COLOR:
      COPY_4V(params, texObj->Sampler.BorderColor.i);
      break;
   default:
      {
         GLint ip[4];
         _mesa_GetTexParameteriv(target, pname, ip);
         params[0] = ip[0];
         if (pname == GL_TEXTURE_SWIZZLE_RGBA_EXT ||
             pname == GL_TEXTURE_CROP_RECT_OES) {
            params[1] = ip[1];
            params[2] = ip[2];
            params[3] = ip[3];
         }
      }
   }
}
