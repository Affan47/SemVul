system_read_qword(bx_address laddr)
{
  Bit64u data;

  unsigned tlbIndex = BX_TLB_INDEX_OF(laddr, 7);
  bx_address lpf = LPFOf(laddr);
  bx_TLB_entry *tlbEntry = &BX_CPU_THIS_PTR TLB.entry[tlbIndex];
  if (tlbEntry->lpf == lpf) {
    bx_hostpageaddr_t hostPageAddr = tlbEntry->hostPageAddr;
    Bit32u pageOffset = PAGE_OFFSET(laddr);
    BX_INSTR_LIN_ACCESS(BX_CPU_ID, laddr, tlbEntry->ppf | pageOffset, 8, BX_READ);
    Bit64u *hostAddr = (Bit64u*) (hostPageAddr | pageOffset);
    ReadHostQWordFromLittleEndian(hostAddr, data);
    BX_DBG_LIN_MEMORY_ACCESS(BX_CPU_ID, laddr,
        tlbEntry->ppf | pageOffset, 8, 0, BX_READ, (Bit8u*) &data);
    return data;
  }

  access_read_linear(laddr, 8, 0, BX_READ, (void *) &data);
  return data;
}
