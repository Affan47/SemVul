read_dereference(s_expression *expr)
{
   s_expression *s_subject;
   s_expression *s_index;
   s_symbol *s_field;

   s_pattern array_pat[] = { "array_ref", s_subject, s_index };
   s_pattern record_pat[] = { "record_ref", s_subject, s_field };

   ir_dereference_variable *var_ref = read_var_ref(expr);
   if (var_ref != NULL) {
      return var_ref;
   } else if (MATCH(expr, array_pat)) {
      ir_rvalue *subject = read_rvalue(s_subject);
      if (subject == NULL) {
	 ir_read_error(NULL, "when reading the subject of an array_ref");
	 return NULL;
      }

      ir_rvalue *idx = read_rvalue(s_index);
      if (idx == NULL) {
	 ir_read_error(NULL, "when reading the index of an array_ref");
	 return NULL;
      }
      return new(mem_ctx) ir_dereference_array(subject, idx);
   } else if (MATCH(expr, record_pat)) {
      ir_rvalue *subject = read_rvalue(s_subject);
      if (subject == NULL) {
	 ir_read_error(NULL, "when reading the subject of a record_ref");
	 return NULL;
      }
      return new(mem_ctx) ir_dereference_record(subject, s_field->value());
   }
   return NULL;
}
