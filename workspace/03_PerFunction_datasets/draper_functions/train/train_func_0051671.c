ARPL_EwGw(bxInstruction_c *i)
{
  Bit16u op2_16, op1_16;

  if (real_mode() || v8086_mode()) {
    BX_DEBUG(("ARPL: not recognized in real or virtual-8086 mode"));
    exception(BX_UD_EXCEPTION, 0, 0);
  }


  if (i->modC0()) {
    op1_16 = BX_READ_16BIT_REG(i->rm());
  }
  else {
    bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

    op1_16 = read_RMW_virtual_word(i->seg(), eaddr);
  }

  op2_16 = BX_READ_16BIT_REG(i->nnn());

  if ((op1_16 & 0x03) < (op2_16 & 0x03)) {
    op1_16 = (op1_16 & 0xfffc) | (op2_16 & 0x03);

    if (i->modC0()) {
      BX_WRITE_16BIT_REG(i->rm(), op1_16);
    }
    else {
      write_RMW_virtual_word(op1_16);
    }
    assert_ZF();
  }
  else {
    clear_ZF();
  }
}
