tex_storage_error_check(struct gl_context *ctx, GLuint dims, GLenum target,
                        GLsizei levels, GLenum internalformat,
                        GLsizei width, GLsizei height, GLsizei depth)
{
   struct gl_texture_object *texObj;

   if (!_mesa_is_legal_tex_storage_format(ctx, internalformat)) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glTexStorage%uD(internalformat = %s)", dims,
                  _mesa_lookup_enum_by_nr(internalformat));
      return GL_TRUE;
   }


   if (width < 1 || height < 1 || depth < 1) {
      _mesa_error(ctx, GL_INVALID_VALUE,
                  "glTexStorage%uD(width, height or depth < 1)", dims);
      return GL_TRUE;
   }


   if (!legal_texobj_target(ctx, dims, target)) {
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glTexStorage%uD(illegal target=%s)",
                  dims, _mesa_lookup_enum_by_nr(target));
      return GL_TRUE;
   }


   if (levels < 1) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glTexStorage%uD(levels < 1)",
                  dims);
      return GL_TRUE;
   }


   if (levels > (GLint) _mesa_max_texture_levels(ctx, target)) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glTexStorage%uD(levels too large)", dims);
      return GL_TRUE;
   }


   if (levels > _mesa_get_tex_max_num_levels(target, width, height, depth)) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glTexStorage%uD(too many levels for max texture dimension)",
                  dims);
      return GL_TRUE;
   }


   texObj = _mesa_get_current_tex_object(ctx, target);
   if (!_mesa_is_proxy_texture(target) && (!texObj || (texObj->Name == 0))) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glTexStorage%uD(texture object 0)", dims);
      return GL_TRUE;
   }


   if (!_mesa_is_proxy_texture(target) && texObj->Immutable) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "glTexStorage%uD(immutable)",
                  dims);
      return GL_TRUE;
   }


   if (!_mesa_legal_texture_base_format_for_target(ctx, target, internalformat,
                                                   dims, "glTexStorage"))
      return GL_TRUE;

   return GL_FALSE;
}
