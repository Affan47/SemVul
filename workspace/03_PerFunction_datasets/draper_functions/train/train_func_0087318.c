fix_unsafe_tree (t)
     tree t;
{
  switch (unsafe_for_reeval (t))
    {
    case 0:
      break;

    case 1:
      t = unsave_expr (t);
      break;

    case 2:
      {
	tree var = build_decl (VAR_DECL, NULL_TREE,
			       TREE_TYPE (t));
	SET_DECL_RTL (var,
		      expand_expr (t, NULL_RTX, VOIDmode, EXPAND_NORMAL));
	t = var;
      }
      break;

    default:
      abort ();
    }
  return t;
}
