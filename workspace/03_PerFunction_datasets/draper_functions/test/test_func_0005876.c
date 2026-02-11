MOV_RdDd(bxInstruction_c *i)
{
  Bit32u val_32;

#if BX_SUPPORT_VMX
  VMexit_DR_Access(i, 1 );
#endif

#if BX_CPU_LEVEL >= 4
  if (BX_CPU_THIS_PTR cr4.get_DE()) {
    if ((i->nnn() & 0xE) == 4) {
      BX_ERROR(("MOV_RdDd: access to DR4/DR5 causes #UD"));
      exception(BX_UD_EXCEPTION, 0, 0);
    }
  }
#endif


  if (BX_CPU_THIS_PTR dr7 & 0x2000) {
    BX_ERROR(("MOV_RdDd: DR7 GD bit is set"));
    BX_CPU_THIS_PTR debug_trap |= BX_DEBUG_DR_ACCESS_BIT;
    exception(BX_DB_EXCEPTION, 0, 0);
  }

  if (!real_mode() && CPL!=0) {
    BX_ERROR(("MOV_RdDd: CPL!=0 not in real mode"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }


  if (!i->modC0())
    BX_PANIC(("MOV_RdDd(): rm field not a register!"));

  switch (i->nnn()) {
    case 0:
    case 1:
    case 2:
    case 3:
      val_32 = (Bit32u) BX_CPU_THIS_PTR dr[i->nnn()];
      break;

    case 4:


    case 6:
      val_32 = BX_CPU_THIS_PTR dr6;
      break;

    case 5:


    case 7:
      val_32 = BX_CPU_THIS_PTR dr7;
      break;

    default:
      BX_ERROR(("MOV_RdDd: #UD - register index out of range"));
      exception(BX_UD_EXCEPTION, 0, 0);
  }

  BX_WRITE_32BIT_REGZ(i->rm(), val_32);
}
