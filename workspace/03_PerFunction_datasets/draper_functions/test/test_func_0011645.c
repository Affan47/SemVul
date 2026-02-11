do_tablejump (rtx index, enum machine_mode mode, rtx range, rtx table_label,
	      rtx default_label, int default_probability)
{
  rtx temp, vector;

  if (INTVAL (range) > cfun->cfg->max_jumptable_ents)
    cfun->cfg->max_jumptable_ents = INTVAL (range);


  if (default_label)
    emit_cmp_and_jump_insns (index, range, GTU, NULL_RTX, mode, 1,
			     default_label, default_probability);


  if (mode != Pmode)
    index = convert_to_mode (Pmode, index, 1);


#ifdef PIC_CASE_VECTOR_ADDRESS
  if (flag_pic && !REG_P (index))
    index = copy_to_mode_reg (Pmode, index);
#endif


  index = gen_rtx_PLUS (Pmode,
			gen_rtx_MULT (Pmode, index,
				      GEN_INT (GET_MODE_SIZE (CASE_VECTOR_MODE))),
			gen_rtx_LABEL_REF (Pmode, table_label));
#ifdef PIC_CASE_VECTOR_ADDRESS
  if (flag_pic)
    index = PIC_CASE_VECTOR_ADDRESS (index);
  else
#endif
    index = memory_address (CASE_VECTOR_MODE, index);
  temp = gen_reg_rtx (CASE_VECTOR_MODE);
  vector = gen_const_mem (CASE_VECTOR_MODE, index);
  convert_move (temp, vector, 0);

  emit_jump_insn (gen_tablejump (temp, table_label));


  if (! CASE_VECTOR_PC_RELATIVE && ! flag_pic)
    emit_barrier ();
}
