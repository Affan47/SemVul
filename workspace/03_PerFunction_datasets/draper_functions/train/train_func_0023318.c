OP_LDMDA2_W(armcpu_t *cpu)
{
     u32 i = cpu->instruction;
     u32 c = 0;

     u32 oldmode;
     u32 start = cpu->R[REG_POS(i,16)];
     u32 * registres;
     u32 * waitState;
     Status_Reg SPSR;

     if(BIT15(i)==0)
     {
          if(cpu->CPSR.bits.mode==USR)
               return 2;
          oldmode = armcpu_switchMode(cpu, SYS);
     }

     registres = cpu->R;
     waitState = MMU.MMU_WAIT32[cpu->proc_ID];

     if(BIT15(i))
     {
          u32 tmp = READ32(cpu->mem_if->data, start);
          registres[15] = tmp & (0XFFFFFFFC | (BIT0(tmp)<<1));
          c += waitState[(start>>24)&0xF];
          start -= 4;
          cpu->next_instruction = registres[15];
     }

     OP_L_DA(14, start);
     OP_L_DA(13, start);
     OP_L_DA(12, start);
     OP_L_DA(11, start);
     OP_L_DA(10, start);
     OP_L_DA(9, start);
     OP_L_DA(8, start);
     OP_L_DA(7, start);
     OP_L_DA(6, start);
     OP_L_DA(5, start);
     OP_L_DA(4, start);
     OP_L_DA(3, start);
     OP_L_DA(2, start);
     OP_L_DA(1, start);
     OP_L_DA(0, start);

     registres[REG_POS(i,16)] = start;

     if(BIT15(i)==0)
     {
          armcpu_switchMode(cpu, oldmode);
          return c + 2;
     }

     SPSR = cpu->SPSR;
     armcpu_switchMode(cpu, SPSR.bits.mode);
     cpu->CPSR=SPSR;
     return c + 2;
}
