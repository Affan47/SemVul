mips64_trigger_exception(cpu_mips_t *cpu,u_int exc_code,int bd_slot)
{
   mips_cp0_t *cp0 = &cpu->cp0;
   m_uint64_t cause,vector;


   if (!(cp0->reg[MIPS_CP0_STATUS] & MIPS_CP0_STATUS_EXL))
   {
      cp0->reg[MIPS_CP0_EPC] = cpu->pc;


      cause = cp0->reg[MIPS_CP0_CAUSE] & MIPS_CP0_CAUSE_IMASK;

      if (bd_slot)
         cause |= MIPS_CP0_CAUSE_BD_SLOT;
      else
         cause &= ~MIPS_CP0_CAUSE_BD_SLOT;

      cause |= (exc_code << MIPS_CP0_CAUSE_SHIFT);
      cp0->reg[MIPS_CP0_CAUSE] = cause;


      vector = 0x180ULL;
   }
   else
   {

      cause = cp0->reg[MIPS_CP0_CAUSE] & MIPS_CP0_CAUSE_IMASK;
      cause |= (exc_code << MIPS_CP0_CAUSE_SHIFT);
      cp0->reg[MIPS_CP0_CAUSE] = cause;


      vector = 0x180ULL;
   }


   cp0->reg[MIPS_CP0_STATUS] |= MIPS_CP0_STATUS_EXL;


   if (cp0->reg[MIPS_CP0_STATUS] & MIPS_CP0_STATUS_BEV)
      cpu->pc = 0xffffffffbfc00200ULL + vector;
   else
      cpu->pc = 0xffffffff80000000ULL + vector;


   cpu->irq_pending = 0;
}
