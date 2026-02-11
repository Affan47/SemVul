OP_STMIB(armcpu_t *cpu)
{
     u32 i = cpu->instruction, c = 0, b;
     u32 start = cpu->R[REG_POS(i,16)];

     for(b=0; b<16; ++b)
     {
          if(BIT_N(i, b))
          {
               start += 4;
               WRITE32(cpu->mem_if->data, start, cpu->R[b]);
               c += MMU.MMU_WAIT32[cpu->proc_ID][(start>>24)&0xF];
          }
     }
     return c + 1;
}
