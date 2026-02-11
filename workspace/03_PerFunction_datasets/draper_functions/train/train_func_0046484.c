execute(void)
{
	struct _Address Source,Destination;
	unsigned long Result, SValue, DValue;
	CMP_Instr Instr;
	Memory_RetrWordFromPC(&Instr.Code);

	TRACE("Source:\n");
	if(!EA_GetFromPC(&Source, 32, Instr.Bits.EAMode, Instr.Bits.EARegister)) return;
	TRACE("Destination:\n");
	if(!EA_GetFromPC(&Destination, 32, 0, Instr.Bits.Register)) return;

	EA_GetValue(&SValue, &Source);
	EA_GetValue(&DValue, &Destination);

	TRACE("Comparing 0x%08lx and 0x%08lx\n", SValue, DValue);

	Result = DValue - SValue;

	SR_Set(I_CMP, SValue, DValue, Result);

	TRACE("Done\n");
	cycle(CMPTime[cycle_EA(Instr.Bits.EARegister,Instr.Bits.EAMode)]);
	return;
}
