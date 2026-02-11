validate_uniform_parameters(struct gl_context *ctx,
			    struct gl_shader_program *shProg,
			    GLint location, GLsizei count,
			    unsigned *loc,
			    unsigned *array_index,
			    const char *caller,
			    bool negative_one_is_not_valid)
{
   if (!shProg || !shProg->LinkStatus) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "%s(program not linked)", caller);
      return false;
   }

   if (location == -1) {


      if (negative_one_is_not_valid) {
	 _mesa_error(ctx, GL_INVALID_OPERATION, "%s(location=%d)",
		     caller, location);
      }

      return false;
   }


   if (count < 0) {
      _mesa_error(ctx, GL_INVALID_VALUE, "%s(count < 0)", caller);
      return false;
   }


   if (location < -1) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "%s(location=%d)",
                  caller, location);
      return false;
   }

   _mesa_uniform_split_location_offset(shProg, location, loc, array_index);

   if (*loc >= shProg->NumUserUniformStorage) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "%s(location=%d)",
		  caller, location);
      return false;
   }

   if (shProg->UniformStorage[*loc].array_elements == 0 && count > 1) {
      _mesa_error(ctx, GL_INVALID_OPERATION,
		  "%s(count > 1 for non-array, location=%d)",
		  caller, location);
      return false;
   }


   unsigned limit = shProg->UniformStorage[*loc].array_elements;
   if (limit == 0)
      limit = 1;
   if (*array_index >= limit) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "%s(location=%d)",
		  caller, location);
      return false;
   }
   return true;
}
