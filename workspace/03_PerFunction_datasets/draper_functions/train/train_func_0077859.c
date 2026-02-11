check_for_override (tree decl, tree ctype)
{
  bool overrides_found = false;
  if (TREE_CODE (decl) == TEMPLATE_DECL)


    return;
  if ((DECL_DESTRUCTOR_P (decl)
       || IDENTIFIER_VIRTUAL_P (DECL_NAME (decl))
       || DECL_CONV_FN_P (decl))
      && look_for_overrides (ctype, decl)
      && !DECL_STATIC_FUNCTION_P (decl))


    {
      DECL_VINDEX (decl) = decl;
      overrides_found = true;
    }

  if (DECL_VIRTUAL_P (decl))
    {
      if (!DECL_VINDEX (decl))
	DECL_VINDEX (decl) = error_mark_node;
      IDENTIFIER_VIRTUAL_P (DECL_NAME (decl)) = 1;
      if (DECL_DESTRUCTOR_P (decl))
	TYPE_HAS_NONTRIVIAL_DESTRUCTOR (ctype) = true;
    }
  else if (DECL_FINAL_P (decl))
    error ("%q+#D marked final, but is not virtual", decl);
  if (DECL_OVERRIDE_P (decl) && !overrides_found)
    error ("%q+#D marked override, but does not override", decl);
}
