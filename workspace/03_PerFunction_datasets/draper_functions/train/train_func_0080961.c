build_field_list (tree t, tree list, int *uses_unions_p)
{
  tree fields;

  *uses_unions_p = 0;


  if (TREE_CODE (t) == UNION_TYPE)
    *uses_unions_p = 1;

  for (fields = TYPE_FIELDS (t); fields; fields = TREE_CHAIN (fields))
    {

      if (TREE_CODE (fields) != FIELD_DECL || DECL_ARTIFICIAL (fields))
	continue;


      if (TREE_CODE (TREE_TYPE (fields)) == UNION_TYPE)
	*uses_unions_p = 1;


      if (ANON_AGGR_TYPE_P (TREE_TYPE (fields)))
	{


	  list = tree_cons (fields, NULL_TREE, list);

	  list = build_field_list (TREE_TYPE (fields), list,
				   uses_unions_p);
	}

      else if (DECL_NAME (fields))
	list = tree_cons (fields, NULL_TREE, list);
    }

  return list;
}
