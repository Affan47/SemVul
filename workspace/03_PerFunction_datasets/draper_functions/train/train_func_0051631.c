add_stmt (tree t)
{
  enum tree_code code = TREE_CODE (t);

  if (CAN_HAVE_LOCATION_P (t) && code != LABEL_EXPR)
    {
      if (!EXPR_HAS_LOCATION (t))
	SET_EXPR_LOCATION (t, input_location);
    }

  if (code == LABEL_EXPR || code == CASE_LABEL_EXPR)
    STATEMENT_LIST_HAS_LABEL (cur_stmt_list) = 1;


  if (!building_stmt_list_p ())
    push_stmt_list ();
  append_to_statement_list_force (t, &cur_stmt_list);

  return t;
}
