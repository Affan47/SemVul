copy_to_mode_reg (enum machine_mode mode, rtx x)
{
  rtx temp = gen_reg_rtx (mode);


  if (! general_operand (x, VOIDmode))
    x = force_operand (x, temp);

  if (GET_MODE (x) != mode && GET_MODE (x) != VOIDmode)
    abort ();
  if (x != temp)
    emit_move_insn (temp, x);
  return temp;
}
