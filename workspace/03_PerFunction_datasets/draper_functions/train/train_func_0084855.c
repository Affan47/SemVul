vzeroall_operation_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1220 "../../../src/gcc/config/i386/predicates.md"
{
  unsigned i, nregs = TARGET_64BIT ? 16 : 8;

  if ((unsigned) XVECLEN (op, 0) != 1 + nregs)
    return false;

  for (i = 0; i < nregs; i++)
    {
      rtx elt = XVECEXP (op, 0, i+1);

      if (GET_CODE (elt) != SET
	  || GET_CODE (SET_DEST (elt)) != REG
	  || GET_MODE (SET_DEST (elt)) != V8SImode
	  || REGNO (SET_DEST (elt)) != SSE_REGNO (i)
	  || SET_SRC (elt) != CONST0_RTX (V8SImode))
	return false;
    }
  return true;
}
