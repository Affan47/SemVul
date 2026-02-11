emit_storent_insn (rtx to, rtx from)
{
  enum machine_mode mode = GET_MODE (to), imode;
  enum insn_code code = optab_handler (storent_optab, mode);
  rtx pattern;

  if (code == CODE_FOR_nothing)
    return false;

  imode = insn_data[code].operand[0].mode;
  if (!insn_data[code].operand[0].predicate (to, imode))
    return false;

  imode = insn_data[code].operand[1].mode;
  if (!insn_data[code].operand[1].predicate (from, imode))
    {
      from = copy_to_mode_reg (imode, from);
      if (!insn_data[code].operand[1].predicate (from, imode))
	return false;
    }

  pattern = GEN_FCN (code) (to, from);
  if (pattern == NULL_RTX)
    return false;

  emit_insn (pattern);
  return true;
}
