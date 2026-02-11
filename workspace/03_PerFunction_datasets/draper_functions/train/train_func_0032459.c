do_assignment(exec_list *instructions, struct _mesa_glsl_parse_state *state,
	      ir_rvalue *lhs, ir_rvalue *rhs, bool is_initializer,
	      YYLTYPE lhs_loc)
{
   void *ctx = state;
   bool error_emitted = (lhs->type->is_error() || rhs->type->is_error());

   if (!error_emitted) {
      if (lhs->variable_referenced() != NULL
          && lhs->variable_referenced()->read_only) {
         _mesa_glsl_error(&lhs_loc, state,
                          "assignment to read-only variable '%s'",
                          lhs->variable_referenced()->name);
         error_emitted = true;

      } else if (!lhs->is_lvalue()) {
	 _mesa_glsl_error(& lhs_loc, state, "non-lvalue in assignment");
	 error_emitted = true;
      }

      if (state->es_shader && lhs->type->is_array()) {
	 _mesa_glsl_error(&lhs_loc, state, "whole array assignment is not "
			  "allowed in GLSL ES 1.00.");
	 error_emitted = true;
      }
   }

   ir_rvalue *new_rhs =
      validate_assignment(state, lhs->type, rhs, is_initializer);
   if (new_rhs == NULL) {
      _mesa_glsl_error(& lhs_loc, state, "type mismatch");
   } else {
      rhs = new_rhs;


      if (lhs->type->array_size() == 0) {
	 ir_dereference *const d = lhs->as_dereference();

	 assert(d != NULL);

	 ir_variable *const var = d->variable_referenced();

	 assert(var != NULL);

	 if (var->max_array_access >= unsigned(rhs->type->array_size())) {

	    _mesa_glsl_error(& lhs_loc, state, "array size must be > %u due to "
			     "previous access",
			     var->max_array_access);
	 }

	 var->type = glsl_type::get_array_instance(lhs->type->element_type(),
						   rhs->type->array_size());
	 d->type = var->type;
      }
      mark_whole_array_access(lhs);
   }

   if (lhs->get_precision() == glsl_precision_undefined)
   {
	   glsl_precision prec = precision_from_ir (rhs);
	   ir_dereference *const d = lhs->as_dereference();
	   if (d)
	   {
		   ir_variable *const var = d->variable_referenced();
		   if (var)
			   var->precision = prec;
	   }
   }


   ir_variable *var = new(ctx) ir_variable(rhs->type, "assignment_tmp",
					   ir_var_temporary, precision_from_ir(rhs));
   ir_dereference_variable *deref_var = new(ctx) ir_dereference_variable(var);
   instructions->push_tail(var);
   instructions->push_tail(new(ctx) ir_assignment(deref_var,
						  rhs,
						  NULL));
   deref_var = new(ctx) ir_dereference_variable(var);

   if (!error_emitted)
      instructions->push_tail(new(ctx) ir_assignment(lhs, deref_var, NULL));

   return new(ctx) ir_dereference_variable(var);
}
