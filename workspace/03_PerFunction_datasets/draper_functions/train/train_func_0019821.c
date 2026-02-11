write_RMW_virtual_byte(Bit8u val8)
{
  BX_DBG_PHY_MEMORY_ACCESS(BX_CPU_ID,
    BX_CPU_THIS_PTR address_xlation.paddress1, 1, BX_WRITE, (Bit8u*) &val8);

  if (BX_CPU_THIS_PTR address_xlation.pages > 2) {

    Bit8u *hostAddr = (Bit8u *) BX_CPU_THIS_PTR address_xlation.pages;
    *hostAddr = val8;
  }
  else {

    access_write_physical(BX_CPU_THIS_PTR address_xlation.paddress1, 1, &val8);
  }
}
