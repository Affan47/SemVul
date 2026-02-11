reparent_ir(exec_list *list, void *mem_ctx)
{
   foreach_list(node, list) {
      visit_tree((ir_instruction *) node, steal_memory, mem_ctx);
   }
}
