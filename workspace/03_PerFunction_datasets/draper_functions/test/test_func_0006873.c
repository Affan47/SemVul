retrofit_lang_decl (tree t)
{
  struct lang_decl *ld;
  size_t size;

  if (CAN_HAVE_FULL_LANG_DECL_P (t))
    size = sizeof (struct lang_decl);
  else
    size = sizeof (struct lang_decl_flags);

  ld = ggc_alloc_cleared (size);

  ld->decl_flags.can_be_full = CAN_HAVE_FULL_LANG_DECL_P (t) ? 1 : 0;
  ld->decl_flags.u1sel = TREE_CODE (t) == NAMESPACE_DECL ? 1 : 0;
  ld->decl_flags.u2sel = 0;
  if (ld->decl_flags.can_be_full)
    ld->u.f.u3sel = TREE_CODE (t) == FUNCTION_DECL ? 1 : 0;

  DECL_LANG_SPECIFIC (t) = ld;
  if (current_lang_name == lang_name_cplusplus
      || decl_linkage (t) == lk_none)
    SET_DECL_LANGUAGE (t, lang_cplusplus);
  else if (current_lang_name == lang_name_c)
    SET_DECL_LANGUAGE (t, lang_c);
  else if (current_lang_name == lang_name_java)
    SET_DECL_LANGUAGE (t, lang_java);
  else abort ();

#ifdef GATHER_STATISTICS
  tree_node_counts[(int)lang_decl] += 1;
  tree_node_sizes[(int)lang_decl] += size;
#endif
}
