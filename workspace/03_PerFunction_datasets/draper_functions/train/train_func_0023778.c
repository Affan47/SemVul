want_inline_function_called_once_p (struct cgraph_node *node)
{
   struct cgraph_node *function = cgraph_function_or_thunk_node (node, NULL);

   if (function->global.inlined_to)
     return false;

   if (!node->callers
       || node->callers->next_caller)
     return false;

   if (cgraph_for_node_and_aliases (node, check_caller_edge, node->callers, true))
     return false;

   if (cgraph_edge_recursive_p (node->callers))
     return false;


   if (DECL_EXTERNAL (function->decl))
     return false;

   if (!cgraph_will_be_removed_from_program_if_no_direct_calls (function))
     return false;
   if (!can_inline_edge_p (node->callers, true))
     return false;
   return true;
}
