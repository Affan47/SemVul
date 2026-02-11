gen_split_2336 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx _val = 0;
  start_sequence ();
#line 664 "../../src/gcc/config/arm/vfp.md"

  if (REGNO (operands[0]) == REGNO (operands[1]))
    {
      operands[0] = gen_highpart (SImode, operands[0]);
      operands[1] = gen_rtx_XOR (SImode, operands[0], GEN_INT (0x80000000));
    }
  else
    {
      rtx in_hi, in_lo, out_hi, out_lo;

      in_hi = gen_rtx_XOR (SImode, gen_highpart (SImode, operands[1]),
			   GEN_INT (0x80000000));
      in_lo = gen_lowpart (SImode, operands[1]);
      out_hi = gen_highpart (SImode, operands[0]);
      out_lo = gen_lowpart (SImode, operands[0]);

      if (REGNO (in_lo) == REGNO (out_hi))
        {
          emit_insn (gen_rtx_SET (SImode, out_lo, in_lo));
	  operands[0] = out_hi;
          operands[1] = in_hi;
        }
      else
        {
          emit_insn (gen_rtx_SET (SImode, out_hi, in_hi));
	  operands[0] = out_lo;
          operands[1] = in_lo;
        }
    }

  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	operand1));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
