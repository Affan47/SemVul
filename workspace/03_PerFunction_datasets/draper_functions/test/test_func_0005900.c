get_cmp_code (enum tree_code orig_cmp_code,
              bool swap_cond, bool invert)
{
  enum tree_code tc = orig_cmp_code;

  if (swap_cond)
    tc = swap_tree_comparison (orig_cmp_code);
  if (invert)
    tc = invert_tree_comparison (tc, false);

  switch (tc)
    {
    case LT_EXPR:
    case LE_EXPR:
    case GT_EXPR:
    case GE_EXPR:
    case EQ_EXPR:
    case NE_EXPR:
      break;
    default:
      return ERROR_MARK;
    }
  return tc;
}
