simplify_gen_subreg (enum machine_mode outermode, rtx op,
		     enum machine_mode innermode, unsigned int byte)
{
  rtx newx;

  newx = simplify_subreg (outermode, op, innermode, byte);
  if (newx)
    return newx;

  if (GET_CODE (op) == SUBREG
      || GET_CODE (op) == CONCAT
      || GET_MODE (op) == VOIDmode)
    return NULL_RTX;

  if (validate_subreg (outermode, innermode, op, byte))
    return gen_rtx_SUBREG (outermode, op, byte);

  return NULL_RTX;
}
