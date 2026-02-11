handle_rvalue(ir_rvalue **rvalue)
   {
      ir_dereference_variable *const dv = (*rvalue)->as_dereference_variable();

      if ((dv != NULL) && (dv->var == this->variable_to_replace)) {
	 this->progress = true;
	 *rvalue = this->value->clone(ralloc_parent(*rvalue), NULL);
      }
   }
