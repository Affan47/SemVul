simplify_gen_subreg (outermode, op, innermode, byte)
     rtx op;
     unsigned int byte;
     enum machine_mode outermode, innermode;
{
  rtx new;

  if (innermode == VOIDmode || outermode == VOIDmode
      || innermode == BLKmode || outermode == BLKmode)
    abort ();

  if (GET_MODE (op) != innermode
      && GET_MODE (op) != VOIDmode)
    abort ();

  if (byte % GET_MODE_SIZE (outermode)
      || byte >= GET_MODE_SIZE (innermode))
    abort ();

  if (GET_CODE (op) == QUEUED)
    return NULL_RTX;

  new = simplify_subreg (outermode, op, innermode, byte);
  if (new)
    return new;

  if (GET_CODE (op) == SUBREG || GET_MODE (op) == VOIDmode)
    return NULL_RTX;

  return gen_rtx_SUBREG (outermode, op, byte);
}
