set_extension( struct gl_context *ctx, const char *name, GLboolean state )
{
   size_t offset;

   if (ctx->Extensions.String) {

      _mesa_problem(ctx, "Trying to enable/disable extension after "
                    "glGetString(GL_EXTENSIONS): %s", name);
      return GL_FALSE;
   }

   offset = name_to_offset(name);
   if (offset == 0) {
      _mesa_problem(ctx, "Trying to enable/disable unknown extension %s",
	            name);
      return GL_FALSE;
   } else if (offset == o(dummy_true) && state == GL_FALSE) {
      _mesa_problem(ctx, "Trying to disable a permanently enabled extension: "
	                  "%s", name);
      return GL_FALSE;
   } else {
      GLboolean *base = (GLboolean *) &ctx->Extensions;
      base[offset] = state;
      return GL_TRUE;
   }
}
