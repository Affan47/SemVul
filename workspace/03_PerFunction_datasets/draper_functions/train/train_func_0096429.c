do_tree_grafting(exec_list *instructions)
{
   ir_variable_refcount_visitor refs;
   struct tree_grafting_info info;

   info.progress = false;
   info.refs = &refs;

   visit_list_elements(info.refs, instructions);

   call_for_basic_blocks(instructions, tree_grafting_basic_block, &info);

   return info.progress;
}
