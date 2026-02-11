_mesa_ActiveTexture(GLenum texture)
{
   const GLuint texUnit = texture - GL_TEXTURE0;
   GLuint k;
   GET_CURRENT_CONTEXT(ctx);


   k = MAX2(ctx->Const.MaxCombinedTextureImageUnits,
            ctx->Const.MaxTextureCoordUnits);

   ASSERT(k <= Elements(ctx->Texture.Unit));

   if (MESA_VERBOSE & (VERBOSE_API|VERBOSE_TEXTURE))
      _mesa_debug(ctx, "glActiveTexture %s\n",
                  _mesa_lookup_enum_by_nr(texture));

   if (texUnit >= k) {
      _mesa_error(ctx, GL_INVALID_ENUM, "glActiveTexture(texture=%s)",
                  _mesa_lookup_enum_by_nr(texture));
      return;
   }

   if (ctx->Texture.CurrentUnit == texUnit)
      return;

   FLUSH_VERTICES(ctx, _NEW_TEXTURE);

   ctx->Texture.CurrentUnit = texUnit;
   if (ctx->Transform.MatrixMode == GL_TEXTURE) {

      ctx->CurrentStack = &ctx->TextureMatrixStack[texUnit];
   }
}
