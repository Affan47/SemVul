m68hc11_is_trap_symbol (sym)
     rtx sym;
{
  if (GET_CODE (sym) == MEM)
    sym = XEXP (sym, 0);

  return trap_handler_symbol != 0 && rtx_equal_p (trap_handler_symbol, sym);
}
