execute(void)
{
	struct _Address Source,Destination;
	unsigned long Result, SValue, DValue;
	CMPI_Instr Instr;
	Memory_RetrWordFromPC(&Instr.Code);

	TRACE("Source:\n");
	if(!EA_GetFromPC(&Source, 32, 7, 4)) return;
	TRACE("Destination:\n");
	if(!EA_GetFromPC(&Destination, 32, 0, Instr.Bits.Register)) return;

	EA_GetValue(&SValue, &Source);
	EA_GetValue(&DValue, &Destination);

	Result = DValue - SValue;

	TRACE("Comparing 0x%08lx with 0x%08lx\n", SValue, DValue);


	SR_Set(I_CMPI, SValue, DValue, Result);

	cycle(CMPITime);

	return;
}
