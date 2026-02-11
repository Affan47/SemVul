gen_split_2457 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx _val = 0;
  start_sequence ();
#line 7805 "../../src/gcc/config/i386/i386.md"
{
  rtx val = operands[2];
  HOST_WIDE_INT len = INTVAL (operands[3]);
  HOST_WIDE_INT pos = INTVAL (operands[4]);
  HOST_WIDE_INT mask;
  enum machine_mode mode, submode;

  mode = GET_MODE (val);
  if (MEM_P (val))
    {


      if (! MEM_VOLATILE_P (val))
	{
	  mode = smallest_mode_for_size (pos + len, MODE_INT);
	  val = adjust_address (val, mode, 0);
	}
    }
  else if (GET_CODE (val) == SUBREG
	   && (submode = GET_MODE (SUBREG_REG (val)),
	       GET_MODE_BITSIZE (mode) > GET_MODE_BITSIZE (submode))
	   && pos + len <= GET_MODE_BITSIZE (submode)
	   && GET_MODE_CLASS (submode) == MODE_INT)
    {

      mode = submode;
      val = SUBREG_REG (val);
    }
  else if (mode == HImode && pos + len <= 8)
    {

      mode = QImode;
      val = gen_lowpart (QImode, val);
    }

  if (len == HOST_BITS_PER_WIDE_INT)
    mask = -1;
  else
    mask = ((HOST_WIDE_INT)1 << len) - 1;
  mask <<= pos;

  operands[2] = gen_rtx_AND (mode, val, gen_int_mode (mask, mode));
}
  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_fmt_ee (GET_CODE (operand1), GET_MODE (operand1),
		operand2,
		const0_rtx)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
