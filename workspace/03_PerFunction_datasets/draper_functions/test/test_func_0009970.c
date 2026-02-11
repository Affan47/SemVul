OP_LDR_P_LSL_IMM_OFF(armcpu_t *cpu)
{
     u32 i = cpu->instruction;
     u32 adr;
     u32 val;
     u32 shift_op;
     LSL_IMM;
     adr = cpu->R[REG_POS(i,16)] + shift_op;
     val = READ32(cpu->mem_if->data, adr);

     if(adr&3)
         val = ROR(val, 8*(adr&3));

     if(REG_POS(i,12)==15)
     {
          cpu->R[15] = val & (0XFFFFFFFC | (((u32)cpu->LDTBit)<<1));
          cpu->CPSR.bits.T = BIT0(val) & cpu->LDTBit;
	      cpu->next_instruction = cpu->R[15];
          return 5 + MMU.MMU_WAIT32[cpu->proc_ID][(adr>>24)&0xF];
     }

     cpu->R[REG_POS(i,12)] = val;

     return 3 + MMU.MMU_WAIT32[cpu->proc_ID][(adr>>24)&0xF];
}
