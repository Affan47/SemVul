OP_LDMDB2_W(armcpu_t *cpu)
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
          u32 tmp;
          start -= 4;
          tmp = READ32(cpu->mem_if->data, start);
          c += waitState[(start>>24)&0xF];
          registres[15] = tmp & (0XFFFFFFFC | (BIT0(tmp)<<1));
          cpu->CPSR = cpu->SPSR;
          cpu->next_instruction = registres[15];
     }

     OP_L_DB(14, start);
     OP_L_DB(13, start);
     OP_L_DB(12, start);
     OP_L_DB(11, start);
     OP_L_DB(10, start);
     OP_L_DB(9, start);
     OP_L_DB(8, start);
     OP_L_DB(7, start);
     OP_L_DB(6, start);
     OP_L_DB(5, start);
     OP_L_DB(4, start);
     OP_L_DB(3, start);
     OP_L_DB(2, start);
     OP_L_DB(1, start);
     OP_L_DB(0, start);

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
