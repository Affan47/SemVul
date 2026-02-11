internal_arg_pointer_based_exp (rtx rtl, bool toplevel)
{
  if (CONSTANT_P (rtl))
    return NULL_RTX;

  if (rtl == crtl->args.internal_arg_pointer)
    return const0_rtx;

  if (REG_P (rtl) && HARD_REGISTER_P (rtl))
    return NULL_RTX;

  if (GET_CODE (rtl) == PLUS && CONST_INT_P (XEXP (rtl, 1)))
    {
      rtx val = internal_arg_pointer_based_exp (XEXP (rtl, 0), toplevel);
      if (val == NULL_RTX || val == pc_rtx)
	return val;
      return plus_constant (val, INTVAL (XEXP (rtl, 1)));
    }


  if (toplevel)
    internal_arg_pointer_based_exp_scan ();

  if (REG_P (rtl))
    {
      unsigned int idx = REGNO (rtl) - FIRST_PSEUDO_REGISTER;
      if (idx < VEC_length (rtx, internal_arg_pointer_exp_state.cache))
	return VEC_index (rtx, internal_arg_pointer_exp_state.cache, idx);

      return NULL_RTX;
    }

  if (for_each_rtx (&rtl, internal_arg_pointer_based_exp_1, NULL))
    return pc_rtx;

  return NULL_RTX;
}
