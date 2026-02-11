dv_from_rtx (rtx x)
{
  decl_or_value dv;

  switch (GET_CODE (x))
    {
    case DEBUG_EXPR:
      dv = dv_from_decl (DEBUG_EXPR_TREE_DECL (x));
      gcc_checking_assert (DECL_RTL_KNOWN_SET (DEBUG_EXPR_TREE_DECL (x)) == x);
      break;

    case VALUE:
      dv = dv_from_value (x);
      break;

    default:
      gcc_unreachable ();
    }

  return dv;
}
