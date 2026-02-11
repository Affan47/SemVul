validate_blend_factors(struct gl_context *ctx, const char *func,
                       GLenum sfactorRGB, GLenum dfactorRGB,
                       GLenum sfactorA, GLenum dfactorA)
{
   if (!legal_src_factor(ctx, sfactorRGB)) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "%s(sfactorRGB = %s)", func,
                  _mesa_lookup_enum_by_nr(sfactorRGB));
      return GL_FALSE;
   }

   if (!legal_dst_factor(ctx, dfactorRGB)) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "%s(dfactorRGB = %s)", func,
                  _mesa_lookup_enum_by_nr(dfactorRGB));
      return GL_FALSE;
   }

   if (sfactorA != sfactorRGB && !legal_src_factor(ctx, sfactorA)) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "%s(sfactorA = %s)", func,
                  _mesa_lookup_enum_by_nr(sfactorA));
      return GL_FALSE;
   }

   if (dfactorA != dfactorRGB && !legal_dst_factor(ctx, dfactorA)) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "%s(dfactorA = %s)", func,
                  _mesa_lookup_enum_by_nr(dfactorA));
      return GL_FALSE;
   }

   return GL_TRUE;
}
