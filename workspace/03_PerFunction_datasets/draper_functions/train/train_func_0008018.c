visit(ir_dereference_variable *ir)
   {
      if (hash_table_find(locals, ir->var) == NULL) {


	 ir_variable *var = linked->symbols->get_variable(ir->var->name);
	 if (var == NULL) {


	    var = ir->var->clone(linked, NULL);
	    linked->symbols->add_variable(var);
	    linked->ir->push_head(var);
	 } else if (var->type->is_array()) {


	    var->max_array_access =
	       MAX2(var->max_array_access, ir->var->max_array_access);

	    if (var->type->length == 0 && ir->var->type->length != 0)
	       var->type = ir->var->type;
	 }

	 ir->var = var;
      }

      return visit_continue;
   }
