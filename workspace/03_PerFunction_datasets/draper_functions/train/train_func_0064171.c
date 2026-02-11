add_default_capture (tree lambda_stack, tree id, tree initializer)
{
  bool this_capture_p = (id == this_identifier);

  tree var = NULL_TREE;

  tree saved_class_type = current_class_type;

  tree node;

  for (node = lambda_stack;
       node;
       node = TREE_CHAIN (node))
    {
      tree lambda = TREE_VALUE (node);

      current_class_type = LAMBDA_EXPR_CLOSURE (lambda);
      var = add_capture (lambda,
                            id,
                            initializer,

			    (!this_capture_p
			     && (LAMBDA_EXPR_DEFAULT_CAPTURE_MODE (lambda)
				 == CPLD_REFERENCE)),
			    false);
      initializer = convert_from_reference (var);
    }

  current_class_type = saved_class_type;

  return var;
}
