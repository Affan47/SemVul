execute(void)
{
	struct _Address Source,Destination;
	unsigned long Result, SValue, DValue;
	long Extend = SRBits->X;
	ADDX_Instr Instr;

	Memory_RetrWordFromPC(&Instr.Code);

	TRACE("Source:\n");
	if(!EA_GetFromPC(&Source, 32, 0, Instr.Bits.RegisterDy)) return;
	TRACE("Destination:\n");
	if(!EA_GetFromPC(&Destination, 32, 0, Instr.Bits.RegisterDx)) return;
	EA_GetValue(&SValue, &Source);
	EA_GetValue(&DValue, &Destination);

	Result = SValue + DValue + Extend;

	TRACE("0x%08lx + 0x%08lx + %d = 0x%08lx\n", SValue, DValue, Extend, Result);

	SR_Set(I_ADDX, SValue, DValue, Result);

	TRACE("Storing Result:\n");
	EA_PutValue(&Destination, Result);

	cycle(ADDXTime);

	return;
}
