c_add_case_label (splay_tree cases, tree cond, tree low_value,
		  tree high_value)
{
  tree type;
  tree label;
  tree case_label;
  splay_tree_node node;


  label = build_decl (LABEL_DECL, NULL_TREE, NULL_TREE);
  DECL_CONTEXT (label) = current_function_decl;


  if (!cond || cond == error_mark_node)
    {


      if (!cases->root)
	add_stmt (build_case_label (NULL_TREE, NULL_TREE, label));
      return error_mark_node;
    }

  if ((low_value && TREE_TYPE (low_value)
       && POINTER_TYPE_P (TREE_TYPE (low_value)))
      || (high_value && TREE_TYPE (high_value)
	  && POINTER_TYPE_P (TREE_TYPE (high_value))))
    error ("pointers are not permitted as case values");


  if (high_value && pedantic)
    pedwarn ("range expressions in switch statements are non-standard");

  type = TREE_TYPE (cond);
  if (low_value)
    {
      low_value = check_case_value (low_value);
      low_value = convert_and_check (type, low_value);
    }
  if (high_value)
    {
      high_value = check_case_value (high_value);
      high_value = convert_and_check (type, high_value);
    }


  if (low_value == error_mark_node || high_value == error_mark_node)
    {
      if (!cases->root)
	add_stmt (build_case_label (NULL_TREE, NULL_TREE, label));
      return error_mark_node;
    }


  if (tree_int_cst_equal (low_value, high_value))
    high_value = NULL_TREE;
  if (low_value && high_value
      && !tree_int_cst_lt (low_value, high_value))
    warning ("empty range specified");


  node = splay_tree_lookup (cases, (splay_tree_key) low_value);


  if (!node && (low_value || high_value))
    {
      splay_tree_node low_bound;
      splay_tree_node high_bound;


      low_bound = splay_tree_predecessor (cases,
					  (splay_tree_key) low_value);
      high_bound = splay_tree_successor (cases,
					 (splay_tree_key) low_value);


      if (low_bound
	  && CASE_HIGH ((tree) low_bound->value)
	  && tree_int_cst_compare (CASE_HIGH ((tree) low_bound->value),
				    low_value) >= 0)
	node = low_bound;


      else if (high_bound
	       && high_value
	       && (tree_int_cst_compare ((tree) high_bound->key,
					 high_value)
		   <= 0))
	node = high_bound;
    }

  if (node)
    {
      tree duplicate = CASE_LABEL_DECL ((tree) node->value);

      if (high_value)
	{
	  error ("duplicate (or overlapping) case value");
	  error ("%Jthis is the first entry overlapping that value", duplicate);
	}
      else if (low_value)
	{
	  error ("duplicate case value") ;
	  error ("%Jpreviously used here", duplicate);
	}
      else
	{
	  error ("multiple default labels in one switch");
	  error ("%Jthis is the first default label", duplicate);
	}
      if (!cases->root)
	add_stmt (build_case_label (NULL_TREE, NULL_TREE, label));
    }


  case_label = add_stmt (build_case_label (low_value, high_value, label));

  splay_tree_insert (cases,
		     (splay_tree_key) low_value,
		     (splay_tree_value) case_label);

  return case_label;
}
