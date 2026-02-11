retrofit_lang_decl (tree t)
{
  struct lang_decl *ld;
  size_t size;
  int sel;

  if (TREE_CODE (t) == FUNCTION_DECL)
    sel = 1, size = sizeof (struct lang_decl_fn);
  else if (TREE_CODE (t) == NAMESPACE_DECL)
    sel = 2, size = sizeof (struct lang_decl_ns);
  else if (TREE_CODE (t) == PARM_DECL)
    sel = 3, size = sizeof (struct lang_decl_parm);
  else if (LANG_DECL_HAS_MIN (t))
    sel = 0, size = sizeof (struct lang_decl_min);
  else
    gcc_unreachable ();

  ld = ggc_alloc_cleared_lang_decl (size);

  ld->u.base.selector = sel;

  DECL_LANG_SPECIFIC (t) = ld;
  if (current_lang_name == lang_name_cplusplus
      || decl_linkage (t) == lk_none)
    SET_DECL_LANGUAGE (t, lang_cplusplus);
  else if (current_lang_name == lang_name_c)
    SET_DECL_LANGUAGE (t, lang_c);
  else if (current_lang_name == lang_name_java)
    SET_DECL_LANGUAGE (t, lang_java);
  else
    gcc_unreachable ();

  if (GATHER_STATISTICS)
    {
      tree_node_counts[(int)lang_decl] += 1;
      tree_node_sizes[(int)lang_decl] += size;
    }
}
