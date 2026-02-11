adjust_debug_stmts (tree from, tree to, basic_block bb)
{
  adjust_info ai;

  if (MAY_HAVE_DEBUG_STMTS
      && TREE_CODE (from) == SSA_NAME
      && ! SSA_NAME_IS_DEFAULT_DEF (from)
      && ! virtual_operand_p (from))
    {
      ai.from = from;
      ai.to = to;
      ai.bb = bb;

      if (adjust_vec.exists ())
	adjust_vec.safe_push (ai);
      else
	adjust_debug_stmts_now (&ai);
    }
}
