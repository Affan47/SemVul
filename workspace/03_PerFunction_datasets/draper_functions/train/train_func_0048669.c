valid_elements_type(struct gl_context *ctx, GLenum type, const char *name)
{
   switch (type) {
   case GL_UNSIGNED_BYTE:
   case GL_UNSIGNED_SHORT:
   case GL_UNSIGNED_INT:
      return true;

   default:
      _mesa_error(ctx, GL_INVALID_ENUM, "%s(type = %s)", name,
                  _mesa_lookup_enum_by_nr(type));
      return false;
   }
}
