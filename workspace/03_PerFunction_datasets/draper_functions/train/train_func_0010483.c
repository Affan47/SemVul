gen_load_of_final_value (reg, final_value)
     rtx reg, final_value;
{
  rtx seq;
  start_sequence ();
  final_value = force_operand (final_value, reg);
  if (final_value != reg)
    emit_move_insn (reg, final_value);
  seq = get_insns ();
  end_sequence ();
  return seq;
}
