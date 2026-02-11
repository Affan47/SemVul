_mesa_GetTexGeniv( GLenum coord, GLenum pname, GLint *params )
{
   struct gl_texture_unit *texUnit;
   struct gl_texgen *texgen;
   GET_CURRENT_CONTEXT(ctx);

   if (ctx->Texture.CurrentUnit >= ctx->Const.MaxTextureCoordUnits) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "glGetTexGeniv(current unit)");
      return;
   }

   texUnit = _mesa_get_current_tex_unit(ctx);

   texgen = get_texgen(ctx, texUnit, coord);
   if (!texgen) {
      _mesa_error(ctx, GL_INVALID_ENUM, "glGetTexGeniv(coord)");
      return;
   }

   switch (pname) {
   case GL_TEXTURE_GEN_MODE:
      params[0] = texgen->Mode;
      break;
   case GL_OBJECT_PLANE:
      if (ctx->API != API_OPENGL_COMPAT) {
         _mesa_error( ctx, GL_INVALID_ENUM, "glGetTexGeniv(param)" );
         return;
      }
      params[0] = (GLint) texgen->ObjectPlane[0];
      params[1] = (GLint) texgen->ObjectPlane[1];
      params[2] = (GLint) texgen->ObjectPlane[2];
      params[3] = (GLint) texgen->ObjectPlane[3];
      break;
   case GL_EYE_PLANE:
      if (ctx->API != API_OPENGL_COMPAT) {
         _mesa_error( ctx, GL_INVALID_ENUM, "glGetTexGeniv(param)" );
         return;
      }
      params[0] = (GLint) texgen->EyePlane[0];
      params[1] = (GLint) texgen->EyePlane[1];
      params[2] = (GLint) texgen->EyePlane[2];
      params[3] = (GLint) texgen->EyePlane[3];
      break;
   default:
      _mesa_error( ctx, GL_INVALID_ENUM, "glGetTexGeniv(pname)" );
   }
}
