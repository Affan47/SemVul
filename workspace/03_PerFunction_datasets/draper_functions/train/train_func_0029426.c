get_attr_opt_enabled (rtx insn ATTRIBUTE_UNUSED)
{
  enum attr_opt cached_opt ATTRIBUTE_UNUSED;

  switch (recog_memoized (insn))
    {
    case 1067:
    case 1066:
    case 1061:
      extract_constrain_insn_cached (insn);
      if ((!((1 << which_alternative) & 0xc)) || ((((1 << which_alternative) & 0xc)) && (
#line 167 "../../src/gcc/config/arm/arm.md"
(optimize_function_for_speed_p (cfun)))))
        {
	  return OPT_ENABLED_YES;
        }
      else
        {
	  return OPT_ENABLED_NO;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
      extract_constrain_insn_cached (insn);
      if ((cached_opt = get_attr_opt (insn)) == OPT_ANY)
        {
	  return OPT_ENABLED_YES;
        }
      else if ((cached_opt == OPT_SPEED) && (
#line 167 "../../src/gcc/config/arm/arm.md"
(optimize_function_for_speed_p (cfun))))
        {
	  return OPT_ENABLED_YES;
        }
      else if ((cached_opt == OPT_SIZE) && (
#line 171 "../../src/gcc/config/arm/arm.md"
(optimize_function_for_size_p (cfun))))
        {
	  return OPT_ENABLED_YES;
        }
      else
        {
	  return OPT_ENABLED_NO;
        }

    default:
      return OPT_ENABLED_YES;

    }
}
