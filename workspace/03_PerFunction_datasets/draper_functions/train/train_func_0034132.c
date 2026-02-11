OP_LDRD_STRD_POST_INDEX( armcpu_t *cpu) {
  u32 i = cpu->instruction;
  u32 Rd_num = REG_POS( i, 12);
  u32 addr = cpu->R[REG_POS(i,16)];
  u32 index;


  if ( BIT22(i))
    index = IMM_OFF;
  else
    index = cpu->R[REG_POS(i,0)];


  if ( BIT23(i))
    cpu->R[REG_POS(i,16)] += index;
  else
    cpu->R[REG_POS(i,16)] -= index;

  if ( !(Rd_num & 0x1)) {

    if ( BIT5(i)) {
      WRITE32(cpu->mem_if->data, addr, cpu->R[Rd_num]);
      WRITE32(cpu->mem_if->data, addr + 4, cpu->R[Rd_num + 1]);
    }
    else {
      cpu->R[Rd_num] = READ32(cpu->mem_if->data, addr);
      cpu->R[Rd_num + 1] = READ32(cpu->mem_if->data, addr + 4);
    }
  }

  return 3 + (MMU.MMU_WAIT32[cpu->proc_ID][(addr>>24)&0xF] * 2);
}
