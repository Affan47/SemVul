get_attr_ce_enabled (rtx insn ATTRIBUTE_UNUSED)
{
  switch (recog_memoized (insn))
    {
    case 3713:
    case 3711:
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return CE_ENABLED_YES;
        }
      else
        {
	  return CE_ENABLED_NO;
        }

    case 3321:
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return CE_ENABLED_NO;
        }
      else if (((1 << which_alternative) & 0x6))
        {
	  return CE_ENABLED_YES;
        }
      else
        {
	  return CE_ENABLED_NO;
        }

    case 3317:
    case 3319:
      extract_constrain_insn_cached (insn);
      if (which_alternative == 0)
        {
	  return CE_ENABLED_NO;
        }
      else
        {
	  return CE_ENABLED_YES;
        }

    case -1:
      if (GET_CODE (PATTERN (insn)) != ASM_INPUT
          && asm_noperands (PATTERN (insn)) < 0)
        fatal_insn_not_found (insn);
    default:
      return CE_ENABLED_YES;

    }
}
