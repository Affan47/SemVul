visit_list_elements(ir_hierarchical_visitor *v, exec_list *l,
                    bool statement_list)
{
   ir_instruction *prev_base_ir = v->base_ir;

   foreach_list_safe(n, l) {
      ir_instruction *const ir = (ir_instruction *) n;
      if (statement_list)
         v->base_ir = ir;
      ir_visitor_status s = ir->accept(v);

      if (s != visit_continue)
	 return s;
   }
   if (statement_list)
      v->base_ir = prev_base_ir;

   return visit_continue;
}
