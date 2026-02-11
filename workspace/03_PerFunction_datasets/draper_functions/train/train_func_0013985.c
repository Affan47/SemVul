cgraph_externally_visible_p (struct cgraph_node *node,
			     bool whole_program, bool aliased)
{
  if (!node->local.finalized)
    return false;
  if (!DECL_COMDAT (node->symbol.decl)
      && (!TREE_PUBLIC (node->symbol.decl)
	  || DECL_EXTERNAL (node->symbol.decl)))
    return false;


  if (aliased)
    return true;


  if (DECL_BUILT_IN (node->symbol.decl))
    return true;


  if (symtab_used_from_object_file_p ((symtab_node) node))
    return true;
  if (DECL_PRESERVE_P (node->symbol.decl))
    return true;
  if (lookup_attribute ("externally_visible",
			DECL_ATTRIBUTES (node->symbol.decl)))
    return true;
  if (TARGET_DLLIMPORT_DECL_ATTRIBUTES
      && lookup_attribute ("dllexport",
			   DECL_ATTRIBUTES (node->symbol.decl)))
    return true;
  if (node->symbol.resolution == LDPR_PREVAILING_DEF_IRONLY)
    return false;


  if ((in_lto_p || whole_program)
      && DECL_COMDAT (node->symbol.decl)
      && cgraph_comdat_can_be_unshared_p (node))
    return false;


  if (in_lto_p
      && (DECL_VISIBILITY (node->symbol.decl) == VISIBILITY_HIDDEN
	  || DECL_VISIBILITY (node->symbol.decl) == VISIBILITY_INTERNAL)


      && node->analyzed)
    ;
  else if (!whole_program)
    return true;

  if (MAIN_NAME_P (DECL_NAME (node->symbol.decl)))
    return true;

  return false;
}
