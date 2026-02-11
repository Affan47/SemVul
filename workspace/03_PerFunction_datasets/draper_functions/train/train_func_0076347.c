armcpu_init(armcpu_t *armcpu, u32 adr)
{
   u32 i;

	armcpu->LDTBit = (armcpu->proc_ID==0);
	armcpu->intVector = 0xFFFF0000 * (armcpu->proc_ID==0);
	armcpu->waitIRQ = FALSE;
	armcpu->wirq = FALSE;

#ifdef GDB_STUB
    armcpu->irq_flag = 0;
#endif

	if(armcpu->coproc[15]) free(armcpu->coproc[15]);

   for(i = 0; i < 15; ++i)
	{
		armcpu->R[i] = 0;
		armcpu->coproc[i] = NULL;
   }

	armcpu->CPSR.val = armcpu->SPSR.val = SYS;

	armcpu->R13_usr = armcpu->R14_usr = 0;
	armcpu->R13_svc = armcpu->R14_svc = 0;
	armcpu->R13_abt = armcpu->R14_abt = 0;
	armcpu->R13_und = armcpu->R14_und = 0;
	armcpu->R13_irq = armcpu->R14_irq = 0;
	armcpu->R8_fiq = armcpu->R9_fiq = armcpu->R10_fiq = armcpu->R11_fiq = armcpu->R12_fiq = armcpu->R13_fiq = armcpu->R14_fiq = 0;

	armcpu->SPSR_svc.val = armcpu->SPSR_abt.val = armcpu->SPSR_und.val = armcpu->SPSR_irq.val = armcpu->SPSR_fiq.val = 0;

#ifdef GDB_STUB
    armcpu->instruct_adr = adr;
	armcpu->R[15] = adr + 8;
#else
	armcpu->R[15] = adr;
#endif

	armcpu->next_instruction = adr;

	armcpu->coproc[15] = (armcp_t*)armcp15_new(armcpu);

#ifndef GDB_STUB
	armcpu_prefetch(armcpu);
#endif
}
