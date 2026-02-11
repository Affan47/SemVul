visit_exec_list(exec_list *list, ir_visitor *visitor)
{
   foreach_iter(exec_list_iterator, iter, *list) {
      ((ir_instruction *)iter.get())->accept(visitor);
   }
}
