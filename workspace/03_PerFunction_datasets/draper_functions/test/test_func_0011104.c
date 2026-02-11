debug_disasm_instruction(bx_address offset)
{
#if BX_DEBUGGER
  bx_dbg_disassemble_current(BX_CPU_ID, 1);
#else
  bx_phy_address phy_addr;
  Bit8u  instr_buf[16];
  char   char_buf[512];
  size_t i=0;

  static char letters[] = "0123456789ABCDEF";
  static disassembler bx_disassemble;
  unsigned remainsInPage = 0x1000 - PAGE_OFFSET(offset);

  bx_bool valid = dbg_xlate_linear2phy(BX_CPU_THIS_PTR get_laddr(BX_SEG_REG_CS, offset), &phy_addr);
  if (valid) {
    BX_MEM(0)->dbg_fetch_mem(BX_CPU_THIS, phy_addr, 16, instr_buf);
    unsigned isize = bx_disassemble.disasm(
        BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.d_b,
        BX_CPU_THIS_PTR cpu_mode == BX_MODE_LONG_64,
        BX_CPU_THIS_PTR get_segment_base(BX_SEG_REG_CS), offset,
        instr_buf, char_buf+i);
    if (isize <= remainsInPage) {
      i=strlen(char_buf);
      char_buf[i++] = ' ';
      char_buf[i++] = ':';
      char_buf[i++] = ' ';
      for (unsigned j=0; j<isize; j++) {
        char_buf[i++] = letters[(instr_buf[j] >> 4) & 0xf];
        char_buf[i++] = letters[(instr_buf[j] >> 0) & 0xf];
      }
      char_buf[i] = 0;
      BX_INFO(("0x" FMT_ADDRX ">> %s", offset, char_buf));
    }
    else {
      BX_INFO(("0x" FMT_ADDRX ": (instruction unavailable) page split instruction", offset));
    }
  }
  else {
    BX_INFO(("0x" FMT_ADDRX ": (instruction unavailable) page not present", offset));
  }
#endif
}
