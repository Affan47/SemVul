m68hc11_make_autoinc_notes (x, data)
     rtx *x;
     void *data;
{
  rtx insn;

  switch (GET_CODE (*x))
    {
    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
      insn = (rtx) data;
      REG_NOTES (insn) = alloc_EXPR_LIST (REG_INC, XEXP (*x, 0),
                                          REG_NOTES (insn));
      return -1;

    default:
      return 0;
    }
}
