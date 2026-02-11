OP_LDRBT_P_LSR_IMM_OFF_POSTIND(armcpu_t *cpu)
{
     u32 oldmode;
     u32 i;
     u32 adr;
     u32 val;
     u32 shift_op;

     if(cpu->CPSR.bits.mode==USR)
          return 2;

     oldmode = armcpu_switchMode(cpu, SYS);

	 LOG("Untested opcode: OP_LDRBT_P_LSR_IMM_OFF_POSTIND");


     i = cpu->instruction;
     LSR_IMM;
     adr = cpu->R[REG_POS(i,16)];
     val = READ8(cpu->mem_if->data, adr);
     cpu->R[REG_POS(i,12)] = val;
     cpu->R[REG_POS(i,16)] = adr + shift_op;

     armcpu_switchMode(cpu, oldmode);

     return 3 + MMU.MMU_WAIT16[cpu->proc_ID][(adr>>24)&0xF];
}
