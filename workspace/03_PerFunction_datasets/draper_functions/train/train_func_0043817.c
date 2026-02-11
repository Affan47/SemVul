process_array_constructor(exec_list *instructions,
			  const glsl_type *constructor_type,
			  YYLTYPE *loc, exec_list *parameters,
			  struct _mesa_glsl_parse_state *state)
{
   void *ctx = state;


   exec_list actual_parameters;
   const unsigned parameter_count =
      process_parameters(instructions, &actual_parameters, parameters, state);

   if ((parameter_count == 0)
       || ((constructor_type->length != 0)
	   && (constructor_type->length != parameter_count))) {
      const unsigned min_param = (constructor_type->length == 0)
	 ? 1 : constructor_type->length;

      _mesa_glsl_error(loc, state, "array constructor must have %s %u "
		       "parameter%s",
		       (constructor_type->length != 0) ? "at least" : "exactly",
		       min_param, (min_param <= 1) ? "" : "s");
      return ir_call::get_error_instruction(ctx);
   }

   if (constructor_type->length == 0) {
      constructor_type =
	 glsl_type::get_array_instance(constructor_type->element_type(),
				       parameter_count);
      assert(constructor_type != NULL);
      assert(constructor_type->length == parameter_count);
   }

   bool all_parameters_are_constant = true;


   foreach_list_safe(n, &actual_parameters) {
      ir_rvalue *ir = (ir_rvalue *) n;
      ir_rvalue *result = ir;


      if (constructor_type->element_type()->is_float()) {
	 const glsl_type *desired_type =
	    glsl_type::get_instance(GLSL_TYPE_FLOAT,
				    ir->type->vector_elements,
				    ir->type->matrix_columns);
	 if (result->type->can_implicitly_convert_to(desired_type)) {


	    result = convert_component(ir, desired_type);
	 }
      }

      if (result->type != constructor_type->element_type()) {
	 _mesa_glsl_error(loc, state, "type error in array constructor: "
			  "expected: %s, found %s",
			  constructor_type->element_type()->name,
			  result->type->name);
      }


      ir_rvalue *const constant = result->constant_expression_value();

      if (constant != NULL)
         result = constant;
      else
         all_parameters_are_constant = false;

      ir->replace_with(result);
   }

   if (all_parameters_are_constant)
      return new(ctx) ir_constant(constructor_type, &actual_parameters);

   ir_variable *var = new(ctx) ir_variable(constructor_type, "array_ctor",
					   ir_var_temporary, glsl_precision_undefined);
   instructions->push_tail(var);

   int i = 0;
   foreach_list(node, &actual_parameters) {
      ir_rvalue *rhs = (ir_rvalue *) node;
      ir_rvalue *lhs = new(ctx) ir_dereference_array(var,
						     new(ctx) ir_constant(i));

      ir_instruction *assignment = new(ctx) ir_assignment(lhs, rhs, NULL);
      instructions->push_tail(assignment);

      i++;
   }

   return new(ctx) ir_dereference_variable(var);
}
