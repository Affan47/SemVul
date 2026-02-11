CLI(bxInstruction_c *i)
{
  Bit32u IOPL = BX_CPU_THIS_PTR get_IOPL();

  if (protected_mode())
  {
#if BX_CPU_LEVEL >= 5
    if (BX_CPU_THIS_PTR cr4.get_PVI() && (CPL == 3))
    {
      if (IOPL < 3) {
        BX_CPU_THIS_PTR clear_VIF();
        return;
      }
    }
    else
#endif
    {
      if (IOPL < CPL) {
        BX_DEBUG(("CLI: IOPL < CPL in protected mode"));
        exception(BX_GP_EXCEPTION, 0, 0);
      }
    }
  }
  else if (v8086_mode())
  {
    if (IOPL != 3) {
#if BX_CPU_LEVEL >= 5
      if (BX_CPU_THIS_PTR cr4.get_VME()) {
        BX_CPU_THIS_PTR clear_VIF();
        return;
      }
#endif
      BX_DEBUG(("CLI: IOPL != 3 in v8086 mode"));
      exception(BX_GP_EXCEPTION, 0, 0);
    }
  }

  BX_CPU_THIS_PTR clear_IF();
}
