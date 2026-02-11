emit_move_via_integer (enum machine_mode mode, rtx x, rtx y, bool force)
{
  enum machine_mode imode;
  enum insn_code code;


  imode = int_mode_for_mode (mode);
  if (imode == BLKmode)
    return NULL_RTX;


  code = optab_handler (mov_optab, imode);
  if (code == CODE_FOR_nothing)
    return NULL_RTX;

  x = emit_move_change_mode (imode, mode, x, force);
  if (x == NULL_RTX)
    return NULL_RTX;
  y = emit_move_change_mode (imode, mode, y, force);
  if (y == NULL_RTX)
    return NULL_RTX;
  return emit_insn (GEN_FCN (code) (x, y));
}
