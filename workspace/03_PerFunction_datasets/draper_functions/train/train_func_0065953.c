cp_emit_debug_info_for_using (tree t, tree context)
{

  if (seen_error ())
    return;


  if (TREE_CODE (t) == FUNCTION_DECL
      && DECL_EXTERNAL (t)
      && DECL_BUILT_IN (t))
    return;


  if (context == global_namespace)
    context = NULL_TREE;

  if (BASELINK_P (t))
    t = BASELINK_FUNCTIONS (t);


  for (t = OVL_CURRENT (t); t; t = OVL_NEXT (t))
    if (TREE_CODE (t) != TEMPLATE_DECL)
      {
	if (building_stmt_list_p ())
	  add_stmt (build_stmt (input_location, USING_STMT, t));
	else
	  (*debug_hooks->imported_module_or_decl) (t, NULL_TREE, context, false);
      }
}
