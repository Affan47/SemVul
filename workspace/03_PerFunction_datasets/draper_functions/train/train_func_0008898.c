storage_type_needs_lowering(ir_dereference_array *deref) const
   {


      const ir_variable *const var = deref->array->variable_referenced();
      if (var == NULL)
	 return this->lower_temps;

      switch (var->mode) {
      case ir_var_auto:
      case ir_var_temporary:
	 return this->lower_temps;
      case ir_var_uniform:
	 return this->lower_uniforms;
      case ir_var_in:
      case ir_var_const_in:
	 return (var->location == -1) ? this->lower_temps : this->lower_inputs;
      case ir_var_out:
	 return (var->location == -1) ? this->lower_temps : this->lower_outputs;
      case ir_var_inout:
	 return this->lower_temps;
      }

      assert(!"Should not get here.");
      return false;
   }
