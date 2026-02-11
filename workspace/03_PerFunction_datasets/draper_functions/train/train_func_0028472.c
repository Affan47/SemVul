simple_move (rtx insn)
{
  rtx x;
  rtx set;
  enum machine_mode mode;

  if (recog_data.n_operands != 2)
    return NULL_RTX;

  set = single_set (insn);
  if (!set)
    return NULL_RTX;

  x = SET_DEST (set);
  if (x != recog_data.operand[0] && x != recog_data.operand[1])
    return NULL_RTX;
  if (!simple_move_operand (x))
    return NULL_RTX;

  x = SET_SRC (set);
  if (x != recog_data.operand[0] && x != recog_data.operand[1])
    return NULL_RTX;


  if (GET_CODE (x) != ASM_OPERANDS
      && !simple_move_operand (x))
    return NULL_RTX;


  mode = GET_MODE (SET_SRC (set));
  if (!SCALAR_INT_MODE_P (mode)
      && (mode_for_size (GET_MODE_SIZE (mode) * BITS_PER_UNIT, MODE_INT, 0)
	  == BLKmode))
    return NULL_RTX;


  if (GET_MODE_CLASS (mode) == MODE_PARTIAL_INT)
    return NULL_RTX;

  return set;
}
