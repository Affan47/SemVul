OP_STMDA2(armcpu_t *cpu)
{
     u32 i, c, b;
     u32 start;
     u32 oldmode;

     if(cpu->CPSR.bits.mode==USR)
          return 2;

     i = cpu->instruction;
     c = 0;
     start = cpu->R[REG_POS(i,16)];
     oldmode = armcpu_switchMode(cpu, SYS);


	 LOG("Untested opcode: OP_STMDA2");

     for(b=0; b<16; ++b)
     {
          if(BIT_N(i, 15-b))
          {
               WRITE32(cpu->mem_if->data, start, cpu->R[15-b]);
               c += MMU.MMU_WAIT32[cpu->proc_ID][(start>>24)&0xF];
               start -= 4;
          }
     }

     armcpu_switchMode(cpu, oldmode);
     return c + 1;
}
