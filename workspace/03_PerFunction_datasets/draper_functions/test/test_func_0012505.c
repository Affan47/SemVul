xg_expand_assembly_insn (IStack *istack, TInsn *orig_insn)
{
  int noperands;
  TInsn new_insn;
  bfd_boolean do_expand;

  tinsn_init (&new_insn);


  if (xg_simplify_insn (orig_insn, &new_insn))
    orig_insn = &new_insn;

  noperands = xtensa_opcode_num_operands (xtensa_default_isa,
					  orig_insn->opcode);
  if (orig_insn->ntok < noperands)
    {
      as_bad (_("found %d operands for '%s':  Expected %d"),
	      orig_insn->ntok,
	      xtensa_opcode_name (xtensa_default_isa, orig_insn->opcode),
	      noperands);
      return TRUE;
    }
  if (orig_insn->ntok > noperands)
    as_warn (_("found too many (%d) operands for '%s':  Expected %d"),
	     orig_insn->ntok,
	     xtensa_opcode_name (xtensa_default_isa, orig_insn->opcode),
	     noperands);


  orig_insn->ntok = noperands;

  if (tinsn_has_invalid_symbolic_operands (orig_insn))
    return TRUE;


  if (orig_insn->opcode == xtensa_extui_opcode)
    {
      int shiftimm = orig_insn->tok[2].X_add_number;
      int maskimm = orig_insn->tok[3].X_add_number;
      if (shiftimm + maskimm > 32)
	{
	  as_bad (_("immediate operands sum to greater than 32"));
	  return TRUE;
	}
    }


  do_expand = (!orig_insn->is_specific_opcode && use_transform ());


  if (is_direct_call_opcode (orig_insn->opcode))
    do_expand = FALSE;

  if (tinsn_has_symbolic_operands (orig_insn))
    {


      if (!tinsn_has_complex_operands (orig_insn))
	do_expand = FALSE;
    }
  else if (xg_immeds_fit (orig_insn))
    do_expand = FALSE;

  if (do_expand)
    xg_assembly_relax (istack, orig_insn, 0, 0, 0, 0, 0);
  else
    istack_push (istack, orig_insn);

  return FALSE;
}
