Pragma_to_gnu (Node_Id gnat_node)
{
  Node_Id gnat_temp;
  tree gnu_result = alloc_stmt_list ();


  if (type_annotate_only
      || !Is_Pragma_Name (Chars (Pragma_Identifier (gnat_node))))
    return gnu_result;

  switch (Get_Pragma_Id (Chars (Pragma_Identifier (gnat_node))))
    {
    case Pragma_Inspection_Point:

      if (global_bindings_p ())
	break;

      for (gnat_temp = First (Pragma_Argument_Associations (gnat_node));
	   Present (gnat_temp);
	   gnat_temp = Next (gnat_temp))
	{
	  Node_Id gnat_expr = Expression (gnat_temp);
	  tree gnu_expr = gnat_to_gnu (gnat_expr);
	  int use_address;
	  enum machine_mode mode;
	  tree asm_constraint = NULL_TREE;
#ifdef ASM_COMMENT_START
	  char *comment;
#endif

	  if (TREE_CODE (gnu_expr) == UNCONSTRAINED_ARRAY_REF)
	    gnu_expr = TREE_OPERAND (gnu_expr, 0);


	  mode = TYPE_MODE (TREE_TYPE (gnu_expr));
	  use_address = ((GET_MODE_CLASS (mode) != MODE_INT
			  && GET_MODE_CLASS (mode) != MODE_PARTIAL_INT)
			 || GET_MODE_SIZE (mode) > UNITS_PER_WORD);

	  if (use_address)
	    gnu_expr = build_unary_op (ADDR_EXPR, NULL_TREE, gnu_expr);

#ifdef ASM_COMMENT_START
	  comment = concat (ASM_COMMENT_START,
			    " inspection point: ",
			    Get_Name_String (Chars (gnat_expr)),
			    use_address ? " address" : "",
			    " is in %0",
			    NULL);
	  asm_constraint = build_string (strlen (comment), comment);
	  free (comment);
#endif
	  gnu_expr = build5 (ASM_EXPR, void_type_node,
			     asm_constraint,
			     NULL_TREE,
			     tree_cons
			     (build_tree_list (NULL_TREE,
					       build_string (1, "g")),
			      gnu_expr, NULL_TREE),
			     NULL_TREE, NULL_TREE);
	  ASM_VOLATILE_P (gnu_expr) = 1;
	  set_expr_location_from_node (gnu_expr, gnat_node);
	  append_to_statement_list (gnu_expr, &gnu_result);
	}
      break;

    case Pragma_Optimize:
      switch (Chars (Expression
		     (First (Pragma_Argument_Associations (gnat_node)))))
	{
	case Name_Off:
	  if (optimize)
	    post_error ("must specify -O0?", gnat_node);
	  break;

	case Name_Space:
	  if (!optimize_size)
	    post_error ("must specify -Os?", gnat_node);
	  break;

	case Name_Time:
	  if (!optimize)
	    post_error ("insufficient -O value?", gnat_node);
	  break;

	default:
	  gcc_unreachable ();
	}
      break;

    case Pragma_Reviewable:
      if (write_symbols == NO_DEBUG)
	post_error ("must specify -g?", gnat_node);
      break;
    }

  return gnu_result;
}
