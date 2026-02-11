shift_result_type(const struct glsl_type *type_a,
                  const struct glsl_type *type_b,
                  ast_operators op,
                  struct _mesa_glsl_parse_state *state, YYLTYPE *loc)
{
   if (!state->check_bitwise_operations_allowed(loc)) {
      return glsl_type::error_type;
   }


   if (!type_a->is_integer()) {
      _mesa_glsl_error(loc, state, "LHS of operator %s must be an integer or "
              "integer vector", ast_expression::operator_string(op));
     return glsl_type::error_type;

   }
   if (!type_b->is_integer()) {
      _mesa_glsl_error(loc, state, "RHS of operator %s must be an integer or "
              "integer vector", ast_expression::operator_string(op));
     return glsl_type::error_type;
   }


   if (type_a->is_scalar() && !type_b->is_scalar()) {
      _mesa_glsl_error(loc, state, "if the first operand of %s is scalar, the "
              "second must be scalar as well",
              ast_expression::operator_string(op));
     return glsl_type::error_type;
   }


   if (type_a->is_vector() &&
      type_b->is_vector() &&
      type_a->vector_elements != type_b->vector_elements) {
      _mesa_glsl_error(loc, state, "vector operands to operator %s must "
              "have same number of elements",
              ast_expression::operator_string(op));
     return glsl_type::error_type;
   }


   return type_a;
}
