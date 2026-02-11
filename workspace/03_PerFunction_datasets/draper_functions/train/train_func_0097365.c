visit(ir_dereference_variable *ir)
{


   if (this->state.is_empty())
      return visit_continue;

   loop_variable_state *const ls =
      (loop_variable_state *) this->state.get_head();

   ir_variable *var = ir->variable_referenced();
   loop_variable *lv = ls->get(var);

   if (lv == NULL) {
      lv = ls->insert(var);
      lv->read_before_write = !this->in_assignee;
   }

   if (this->in_assignee) {
      assert(this->current_assignment != NULL);

      lv->conditional_assignment = (this->if_statement_depth > 0)
	 || (this->current_assignment->condition != NULL);

      if (lv->first_assignment == NULL) {
	 assert(lv->num_assignments == 0);

	 lv->first_assignment = this->current_assignment;
      }

      lv->num_assignments++;
   } else if (lv->first_assignment == this->current_assignment) {


      lv->read_before_write = true;
   }

   return visit_continue;
}
