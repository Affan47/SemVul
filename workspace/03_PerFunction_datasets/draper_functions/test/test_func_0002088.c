extract_bit_field_using_extv (const extraction_insn *extv, rtx op0,
			      unsigned HOST_WIDE_INT bitsize,
			      unsigned HOST_WIDE_INT bitnum,
			      int unsignedp, rtx target,
			      enum machine_mode mode, enum machine_mode tmode)
{
  struct expand_operand ops[4];
  rtx spec_target = target;
  rtx spec_target_subreg = 0;
  enum machine_mode ext_mode = extv->field_mode;
  unsigned unit = GET_MODE_BITSIZE (ext_mode);

  if (bitsize == 0 || unit < bitsize)
    return NULL_RTX;

  if (MEM_P (op0))

    op0 = narrow_bit_field_mem (op0, extv->struct_mode, bitsize, bitnum,
				&bitnum);
  else
    {

      if (BYTES_BIG_ENDIAN)
	bitnum += unit - GET_MODE_BITSIZE (GET_MODE (op0));


      if (GET_CODE (op0) == SUBREG && GET_MODE (op0) != ext_mode)
	return NULL_RTX;
      if (REG_P (op0) && GET_MODE (op0) != ext_mode)
	op0 = gen_lowpart_SUBREG (ext_mode, op0);
    }


  if (BITS_BIG_ENDIAN != BYTES_BIG_ENDIAN)
    bitnum = unit - bitsize - bitnum;

  if (target == 0)
    target = spec_target = gen_reg_rtx (tmode);

  if (GET_MODE (target) != ext_mode)
    {


      if (REG_P (target)
	  && TRULY_NOOP_TRUNCATION_MODES_P (GET_MODE (target), ext_mode))
	{
	  target = gen_lowpart (ext_mode, target);
	  if (GET_MODE_PRECISION (ext_mode)
	      > GET_MODE_PRECISION (GET_MODE (spec_target)))
	    spec_target_subreg = target;
	}
      else
	target = gen_reg_rtx (ext_mode);
    }

  create_output_operand (&ops[0], target, ext_mode);
  create_fixed_operand (&ops[1], op0);
  create_integer_operand (&ops[2], bitsize);
  create_integer_operand (&ops[3], bitnum);
  if (maybe_expand_insn (extv->icode, 4, ops))
    {
      target = ops[0].value;
      if (target == spec_target)
	return target;
      if (target == spec_target_subreg)
	return spec_target;
      return convert_extracted_bit_field (target, mode, tmode, unsignedp);
    }
  return NULL_RTX;
}
