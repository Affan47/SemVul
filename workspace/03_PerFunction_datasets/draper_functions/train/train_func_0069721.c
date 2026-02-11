finish_goto_stmt (tree destination)
{
  if (TREE_CODE (destination) == IDENTIFIER_NODE)
    destination = lookup_label (destination);


  if (TREE_CODE (destination) == LABEL_DECL)
    TREE_USED (destination) = 1;
  else
    {

      if (!processing_template_decl)
	destination = decay_conversion (destination);


      DECL_UNINLINABLE (current_function_decl) = 1;
    }

  check_goto (destination);

  return add_stmt (build_stmt (GOTO_STMT, destination));
}
