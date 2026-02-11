eliminate_push_avail (tree op)
{
  tree valnum = VN_INFO (op)->valnum;
  if (TREE_CODE (valnum) == SSA_NAME)
    {
      if (el_avail.length () <= SSA_NAME_VERSION (valnum))
	el_avail.safe_grow_cleared (SSA_NAME_VERSION (valnum) + 1);
      el_avail[SSA_NAME_VERSION (valnum)] = op;
      el_avail_stack.safe_push (op);
    }
}
