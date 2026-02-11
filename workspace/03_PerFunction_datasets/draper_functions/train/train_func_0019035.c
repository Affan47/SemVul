verify_symtab_node (symtab_node node)
{
  if (seen_error ())
    return;

  timevar_push (TV_CGRAPH_VERIFY);
  if (cgraph_node *cnode = dyn_cast <cgraph_node> (node))
    verify_cgraph_node (cnode);
  else
    if (verify_symtab_base (node))
      {
        dump_symtab_node (stderr, node);
        internal_error ("verify_symtab_node failed");
      }
  timevar_pop (TV_CGRAPH_VERIFY);
}
