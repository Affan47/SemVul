ipa_sra_preliminary_function_checks (struct cgraph_node *node)
{
  if (!cgraph_node_can_be_local_p (node))
    {
      if (dump_file)
	fprintf (dump_file, "Function not local to this compilation unit.\n");
      return false;
    }

  if (!node->local.can_change_signature)
    {
      if (dump_file)
	fprintf (dump_file, "Function can not change signature.\n");
      return false;
    }

  if (!tree_versionable_function_p (node->decl))
    {
      if (dump_file)
	fprintf (dump_file, "Function is not versionable.\n");
      return false;
    }

  if (DECL_VIRTUAL_P (current_function_decl))
    {
      if (dump_file)
	fprintf (dump_file, "Function is a virtual method.\n");
      return false;
    }

  if ((DECL_COMDAT (node->decl) || DECL_EXTERNAL (node->decl))
      && inline_summary(node)->size >= MAX_INLINE_INSNS_AUTO)
    {
      if (dump_file)
	fprintf (dump_file, "Function too big to be made truly local.\n");
      return false;
    }

  if (!node->callers)
    {
      if (dump_file)
	fprintf (dump_file,
		 "Function has no callers in this compilation unit.\n");
      return false;
    }

  if (cfun->stdarg)
    {
      if (dump_file)
	fprintf (dump_file, "Function uses stdarg. \n");
      return false;
    }

  if (TYPE_ATTRIBUTES (TREE_TYPE (node->decl)))
    return false;

  return true;
}
