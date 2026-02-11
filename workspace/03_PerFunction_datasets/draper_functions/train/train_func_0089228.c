OP_LSL_REG(armcpu_t *cpu)
{
     u32 i = cpu->instruction;
     u32 v = cpu->R[REG_NUM(i, 3)]&0xFF;

     if(!v)
     {
          cpu->CPSR.bits.N = BIT31(cpu->R[REG_NUM(i, 0)]);
          cpu->CPSR.bits.Z = cpu->R[REG_NUM(i, 0)] == 0;
          return 3;
     }
     if(v<32)
     {
          cpu->CPSR.bits.C = BIT_N(cpu->R[REG_NUM(i, 0)], 32-v);
          cpu->R[REG_NUM(i, 0)] <<= v;
          cpu->CPSR.bits.N = BIT31(cpu->R[REG_NUM(i, 0)]);
          cpu->CPSR.bits.Z = cpu->R[REG_NUM(i, 0)] == 0;
          return 3;
     }
     if(v==32)
          cpu->CPSR.bits.C = BIT0(cpu->R[REG_NUM(i, 0)]);
     else
          cpu->CPSR.bits.C = 0;
     cpu->R[REG_NUM(i, 0)] = 0;
     cpu->CPSR.bits.N = 0;
     cpu->CPSR.bits.Z = 1;

     return 3;
}
