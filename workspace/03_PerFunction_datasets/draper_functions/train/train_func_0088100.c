accept(ir_hierarchical_visitor *v)
{
   ir_visitor_status s = v->visit_enter(this);
   if (s != visit_continue)
      return (s == visit_continue_with_parent) ? visit_continue : s;

   s = this->condition->accept(v);
   if (s != visit_continue)
      return (s == visit_continue_with_parent) ? visit_continue : s;

   if (s != visit_continue_with_parent) {
      s = visit_list_elements(v, &this->then_instructions);
      if (s == visit_stop)
	 return s;
   }

   if (s != visit_continue_with_parent) {
      s = visit_list_elements(v, &this->else_instructions);
      if (s == visit_stop)
	 return s;
   }

   return v->visit_leave(this);
}
