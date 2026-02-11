_mesa_ActiveStencilFaceEXT(GLenum face)
{
   GET_CURRENT_CONTEXT(ctx);

   if (MESA_VERBOSE & VERBOSE_API)
      _mesa_debug(ctx, "glActiveStencilFaceEXT()\n");

   if (!ctx->Extensions.EXT_stencil_two_side) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "glActiveStencilFaceEXT");
      return;
   }

   if (face == GL_FRONT || face == GL_BACK) {
      ctx->Stencil.ActiveFace = (face == GL_FRONT) ? 0 : 2;
   }
   else {
      _mesa_error(ctx, GL_INVALID_ENUM, "glActiveStencilFaceEXT(face)");
   }
}
