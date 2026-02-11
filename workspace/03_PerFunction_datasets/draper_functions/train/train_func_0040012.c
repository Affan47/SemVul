finish_compound_literal (tree type, tree initializer_list)
{
  tree compound_literal;


  compound_literal = build_constructor (NULL_TREE, initializer_list);

  TREE_HAS_CONSTRUCTOR (compound_literal) = 1;
  if (processing_template_decl)
    TREE_TYPE (compound_literal) = type;
  else
    {

      compound_literal = digest_init (type, compound_literal, NULL);


      if (TREE_CODE (type) == ARRAY_TYPE && !COMPLETE_TYPE_P (type))
	complete_array_type (type, compound_literal, 1);
    }

  return compound_literal;
}
