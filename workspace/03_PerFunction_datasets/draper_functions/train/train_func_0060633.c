cross_validate_outputs_to_inputs(struct gl_shader_program *prog,
				 gl_shader *producer, gl_shader *consumer)
{
   glsl_symbol_table parameters;

   const char *const producer_stage = "vertex";
   const char *const consumer_stage = "fragment";


   foreach_list(node, producer->ir) {
      ir_variable *const var = ((ir_instruction *) node)->as_variable();


      if ((var == NULL) || (var->mode != ir_var_out))
	 continue;

      parameters.add_variable(var);
   }


   foreach_list(node, consumer->ir) {
      ir_variable *const input = ((ir_instruction *) node)->as_variable();


      if ((input == NULL) || (input->mode != ir_var_in))
	 continue;

      ir_variable *const output = parameters.get_variable(input->name);
      if (output != NULL) {


	 if (input->type != output->type) {


	    if (!output->type->is_array()
		|| (strncmp("gl_", output->name, 3) != 0)) {
	       linker_error(prog,
			    "%s shader output `%s' declared as type `%s', "
			    "but %s shader input declared as type `%s'\n",
			    producer_stage, output->name,
			    output->type->name,
			    consumer_stage, input->type->name);
	       return false;
	    }
	 }


	 if (input->centroid != output->centroid) {
	    linker_error(prog,
			 "%s shader output `%s' %s centroid qualifier, "
			 "but %s shader input %s centroid qualifier\n",
			 producer_stage,
			 output->name,
			 (output->centroid) ? "has" : "lacks",
			 consumer_stage,
			 (input->centroid) ? "has" : "lacks");
	    return false;
	 }

	 if (input->invariant != output->invariant) {
	    linker_error(prog,
			 "%s shader output `%s' %s invariant qualifier, "
			 "but %s shader input %s invariant qualifier\n",
			 producer_stage,
			 output->name,
			 (output->invariant) ? "has" : "lacks",
			 consumer_stage,
			 (input->invariant) ? "has" : "lacks");
	    return false;
	 }

	 if (input->interpolation != output->interpolation) {
	    linker_error(prog,
			 "%s shader output `%s' specifies %s "
			 "interpolation qualifier, "
			 "but %s shader input specifies %s "
			 "interpolation qualifier\n",
			 producer_stage,
			 output->name,
			 output->interpolation_string(),
			 consumer_stage,
			 input->interpolation_string());
	    return false;
	 }
      }
   }

   return true;
}
