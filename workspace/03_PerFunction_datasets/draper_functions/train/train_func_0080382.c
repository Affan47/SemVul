SiS_SetCRT1Group(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		 unsigned short ModeIdIndex)
{
	unsigned short StandTableIndex, rrti;

	SiS_Pr->SiS_CRT1Mode = ModeNo;

	if (ModeNo <= 0x13)
		StandTableIndex = 0;
	else
		StandTableIndex = 1;

	SiS_ResetSegmentRegisters(SiS_Pr);
	SiS_SetSeqRegs(SiS_Pr, StandTableIndex);
	SiS_SetMiscRegs(SiS_Pr, StandTableIndex);
	SiS_SetCRTCRegs(SiS_Pr, StandTableIndex);
	SiS_SetATTRegs(SiS_Pr, StandTableIndex);
	SiS_SetGRCRegs(SiS_Pr, StandTableIndex);
	SiS_ClearExt1Regs(SiS_Pr, ModeNo);

	rrti = SiS_GetRatePtr(SiS_Pr, ModeNo, ModeIdIndex);

	if (rrti != 0xFFFF) {
		SiS_SetCRT1Sync(SiS_Pr, rrti);
		SiS_SetCRT1CRTC(SiS_Pr, ModeNo, ModeIdIndex, rrti);
		SiS_SetCRT1Offset(SiS_Pr, ModeNo, ModeIdIndex, rrti);
		SiS_SetCRT1VCLK(SiS_Pr, ModeNo, rrti);
	}

	SiS_SetCRT1FIFO_310(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_SetCRT1ModeRegs(SiS_Pr, ModeNo, ModeIdIndex, rrti);

	SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_DisplayOn(SiS_Pr);
}
