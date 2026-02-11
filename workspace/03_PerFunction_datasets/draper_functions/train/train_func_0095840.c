genrtl_decl_stmt (tree t)
{
  tree decl;
  emit_line_note (input_location);
  decl = DECL_STMT_DECL (t);


  if (TREE_CODE (decl) == VAR_DECL
      && !TREE_STATIC (decl)
      && !DECL_EXTERNAL (decl))
    {

      if (!anon_aggr_type_p (TREE_TYPE (decl)))
	emit_local_var (decl);
      else
	expand_anon_union_decl (decl, NULL_TREE,
				DECL_ANON_UNION_ELEMS (decl));
    }
  else if (TREE_CODE (decl) == VAR_DECL && TREE_STATIC (decl))
    make_rtl_for_local_static (decl);
  else if (TREE_CODE (decl) == LABEL_DECL
	   && C_DECLARED_LABEL_FLAG (decl))
    declare_nonlocal_label (decl);
  else if (lang_expand_decl_stmt)
    (*lang_expand_decl_stmt) (t);
}
