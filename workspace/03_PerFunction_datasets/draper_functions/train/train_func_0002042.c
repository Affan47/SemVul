set_type_package_list (tree type)
{
  int i;
  const char *type_string = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type)));
  const char *ptr;
  int qualifications;
  tree list = NULL_TREE, elt;

  for (ptr = type_string, qualifications = 0; *ptr; ptr++)
    if (*ptr == '.')
      qualifications += 1;

  for (ptr = type_string, i = 0; i < qualifications; ptr++)
    {
      if (ptr [0] == '.')
	{
	  tree const identifier
	    = get_identifier_with_length (type_string, ptr - type_string);

	  elt = build_tree_list (identifier, identifier);
	  TREE_CHAIN (elt) = list;
	  list = elt;
	  type_string = ptr+1;
	  i += 1;
	}
    }

  elt = build_tree_list (type, get_identifier (type_string));
  TREE_CHAIN (elt) = list;
  list = elt;
  TYPE_PACKAGE_LIST (type) = nreverse (list);
}
