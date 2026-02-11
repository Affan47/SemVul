update_array_sizes(struct gl_shader_program *prog)
{
   for (unsigned i = 0; i < MESA_SHADER_TYPES; i++) {
	 if (prog->_LinkedShaders[i] == NULL)
	    continue;

      foreach_list(node, prog->_LinkedShaders[i]->ir) {
	 ir_variable *const var = ((ir_instruction *) node)->as_variable();

	 if ((var == NULL) || (var->mode != ir_var_uniform &&
			       var->mode != ir_var_in &&
			       var->mode != ir_var_out) ||
	     !var->type->is_array())
	    continue;

	 unsigned int size = var->max_array_access;
	 for (unsigned j = 0; j < MESA_SHADER_TYPES; j++) {
	       if (prog->_LinkedShaders[j] == NULL)
		  continue;

	    foreach_list(node2, prog->_LinkedShaders[j]->ir) {
	       ir_variable *other_var = ((ir_instruction *) node2)->as_variable();
	       if (!other_var)
		  continue;

	       if (strcmp(var->name, other_var->name) == 0 &&
		   other_var->max_array_access > size) {
		  size = other_var->max_array_access;
	       }
	    }
	 }

	 if (size + 1 != var->type->fields.array->length) {


	    if (var->num_state_slots > 0) {
	       var->num_state_slots = (size + 1)
		  * (var->num_state_slots / var->type->length);
	    }

	    var->type = glsl_type::get_array_instance(var->type->fields.array,
						      size + 1);


	 }
      }
   }
}
