variable_size (tree size)
{
  tree save;


  if (TREE_CONSTANT (size)
      || (*lang_hooks.decls.global_bindings_p) () < 0
      || CONTAINS_PLACEHOLDER_P (size))
    return size;

  if (TREE_CODE (size) == MINUS_EXPR && integer_onep (TREE_OPERAND (size, 1)))


    TREE_OPERAND (size, 0) = save = save_expr (TREE_OPERAND (size, 0));
  else
    size = save = save_expr (size);


  if (TREE_CODE (save) == SAVE_EXPR)
    SAVE_EXPR_PERSISTENT_P (save) = 1;

  if ((*lang_hooks.decls.global_bindings_p) ())
    {
      if (TREE_CONSTANT (size))
	error ("type size can't be explicitly evaluated");
      else
	error ("variable-size type declared outside of any function");

      return size_one_node;
    }

  if (immediate_size_expand)
    expand_expr (save, const0_rtx, VOIDmode, 0);
  else if (cfun != 0 && cfun->x_dont_save_pending_sizes_p)


    ;
  else
    put_pending_size (save);

  return size;
}
