group_case_nodes (case_node_ptr head)
{
  case_node_ptr node = head;

  while (node)
    {
      rtx lab = label_rtx (node->code_label);
      case_node_ptr np = node;


      while (((np = np->right) != 0)

	     && same_case_target_p (label_rtx (np->code_label), lab)

	     && tree_int_cst_equal (np->low,
				    fold (build (PLUS_EXPR,
						 TREE_TYPE (node->high),
						 node->high,
						 integer_one_node)))

	     && tree_int_cst_lt (node->high,
				 fold (build (PLUS_EXPR,
					      TREE_TYPE (node->high),
					      node->high,
					      integer_one_node))))
	{
	  node->high = np->high;
	}


      node->right = np;
      node = np;
    }
}
