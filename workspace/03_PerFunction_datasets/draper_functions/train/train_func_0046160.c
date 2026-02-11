read_type(s_expression *expr)
{
   s_expression *s_base_type;
   s_int *s_size;

   s_pattern pat[] = { "array", s_base_type, s_size };
   if (MATCH(expr, pat)) {
      const glsl_type *base_type = read_type(s_base_type);
      if (base_type == NULL) {
	 ir_read_error(NULL, "when reading base type of array type");
	 return NULL;
      }

      return glsl_type::get_array_instance(base_type, s_size->value());
   }

   s_symbol *type_sym = SX_AS_SYMBOL(expr);
   if (type_sym == NULL) {
      ir_read_error(expr, "expected <type>");
      return NULL;
   }

   const glsl_type *type = state->symbols->get_type(type_sym->value());
   if (type == NULL)
      ir_read_error(expr, "invalid type: %s", type_sym->value());

   return type;
}
