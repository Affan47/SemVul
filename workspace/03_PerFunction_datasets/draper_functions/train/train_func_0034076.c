create_one_component_var (tree type, tree orig, const char *prefix,
			  const char *suffix, enum tree_code code)
{
  tree r = create_tmp_var (type, prefix);
  add_referenced_var (r);

  DECL_SOURCE_LOCATION (r) = DECL_SOURCE_LOCATION (orig);
  DECL_ARTIFICIAL (r) = 1;

  if (DECL_NAME (orig) && !DECL_IGNORED_P (orig))
    {
      const char *name = IDENTIFIER_POINTER (DECL_NAME (orig));

      DECL_NAME (r) = get_identifier (ACONCAT ((name, suffix, NULL)));

      SET_DECL_DEBUG_EXPR (r, build1 (code, type, orig));
      DECL_DEBUG_EXPR_IS_FROM (r) = 1;
      DECL_IGNORED_P (r) = 0;
      TREE_NO_WARNING (r) = TREE_NO_WARNING (orig);
    }
  else
    {
      DECL_IGNORED_P (r) = 1;
      TREE_NO_WARNING (r) = 1;
    }

  return r;
}
