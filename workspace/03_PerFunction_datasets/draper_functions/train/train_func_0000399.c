any_external_decl (tree id)
{
  tree decl = IDENTIFIER_SYMBOL_VALUE (id);
  tree t;

  if (decl == 0 || TREE_CODE (decl) == ERROR_MARK)
    return 0;
  else if (TREE_CODE (decl) != TYPE_DECL && DECL_EXTERNAL (decl))
    return decl;

  t = purpose_member (id, truly_local_externals);
  if (t)
    return TREE_VALUE (t);

  return 0;
}
