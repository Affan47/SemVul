modulus_result_type(const struct glsl_type *type_a,
		    const struct glsl_type *type_b,
		    struct _mesa_glsl_parse_state *state, YYLTYPE *loc)
{
   if (state->language_version < 130) {
      _mesa_glsl_error(loc, state,
                       "operator '%%' is reserved in %s",
                       state->version_string);
      return glsl_type::error_type;
   }


   if (!type_a->is_integer()) {
      _mesa_glsl_error(loc, state, "LHS of operator %% must be an integer.");
      return glsl_type::error_type;
   }
   if (!type_b->is_integer()) {
      _mesa_glsl_error(loc, state, "RHS of operator %% must be an integer.");
      return glsl_type::error_type;
   }
   if (type_a->base_type != type_b->base_type) {
      _mesa_glsl_error(loc, state,
		       "operands of %% must have the same base type");
      return glsl_type::error_type;
   }


   if (type_a->is_vector()) {
      if (!type_b->is_vector()
	  || (type_a->vector_elements == type_b->vector_elements))
	 return type_a;
   } else
      return type_b;


   _mesa_glsl_error(loc, state, "type mismatch");
   return glsl_type::error_type;
}
