cplus_decl_attributes (tree *decl, tree attributes, int flags)
{
  if (*decl == NULL_TREE || *decl == void_type_node)
    return;

  if (TREE_CODE (*decl) == TEMPLATE_DECL)
    decl = &DECL_TEMPLATE_RESULT (*decl);

  decl_attributes (decl, attributes, flags);

  if (TREE_CODE (*decl) == TYPE_DECL)
    SET_IDENTIFIER_TYPE_VALUE (DECL_NAME (*decl), TREE_TYPE (*decl));
}
