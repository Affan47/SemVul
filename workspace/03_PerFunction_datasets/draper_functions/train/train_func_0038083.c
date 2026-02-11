prepare_eh_table_type (tree type)
{
  tree exp;
  tree *slot;
  const char *name;
  char *buf;
  tree decl;
  tree utf8_ref;


  if (type == NULL_TREE)
    return NULL_TREE;

  if (TYPE_TO_RUNTIME_MAP (output_class) == NULL)
    TYPE_TO_RUNTIME_MAP (output_class) = java_treetreehash_create (10);

  slot = java_treetreehash_new (TYPE_TO_RUNTIME_MAP (output_class), type);
  if (*slot != NULL)
    return TREE_VALUE (*slot);

  if (is_compiled_class (type) && !flag_indirect_dispatch)
    {
      name = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type)));
      buf = (char *) alloca (strlen (name) + 5);
      sprintf (buf, "%s_ref", name);
      decl = build_decl (input_location,
			 VAR_DECL, get_identifier (buf), ptr_type_node);
      TREE_STATIC (decl) = 1;
      DECL_ARTIFICIAL (decl) = 1;
      DECL_IGNORED_P (decl) = 1;
      TREE_READONLY (decl) = 1;
      TREE_THIS_VOLATILE (decl) = 0;
      DECL_INITIAL (decl) = build_class_ref (type);
      layout_decl (decl, 0);
      pushdecl (decl);
      exp = build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (decl)), decl);
    }
  else
    {
      utf8_ref = build_utf8_ref (DECL_NAME (TYPE_NAME (type)));
      name = IDENTIFIER_POINTER (DECL_NAME (TREE_OPERAND (utf8_ref, 0)));
      buf = (char *) alloca (strlen (name) + 5);
      sprintf (buf, "%s_ref", name);
      decl = build_decl (input_location,
			 VAR_DECL, get_identifier (buf), utf8const_ptr_type);
      TREE_STATIC (decl) = 1;
      DECL_ARTIFICIAL (decl) = 1;
      DECL_IGNORED_P (decl) = 1;
      TREE_READONLY (decl) = 1;
      TREE_THIS_VOLATILE (decl) = 0;
      layout_decl (decl, 0);
      pushdecl (decl);
      exp = build1 (ADDR_EXPR, build_pointer_type (utf8const_ptr_type), decl);
      CONSTRUCTOR_APPEND_ELT (TYPE_CATCH_CLASSES (output_class),
			      NULL_TREE,
			      make_catch_class_record (exp, utf8_ref));
    }

  exp = convert (ptr_type_node, exp);

  *slot = tree_cons (type, exp, NULL_TREE);

  return exp;
}
