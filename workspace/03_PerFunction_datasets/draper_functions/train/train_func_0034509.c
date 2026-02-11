SiSUSBSetMode(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
	unsigned short ModeIdIndex;
	unsigned long BaseAddr = SiS_Pr->IOAddress;

	SiSUSB_InitPtr(SiS_Pr);
	SiSUSBRegInit(SiS_Pr, BaseAddr);
	SiS_GetSysFlags(SiS_Pr);

	if (!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex)))
		return 0;

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x05, 0x86);

	SiSInitPCIetc(SiS_Pr);

	ModeNo &= 0x7f;

	SiS_Pr->SiS_ModeType =
	    SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag & ModeTypeMask;

	SiS_Pr->SiS_SetFlag = LowModeTests;


	SiS_SetCRT1Group(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_HandleCRT1(SiS_Pr);

	SiS_DisplayOn(SiS_Pr);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c6, 0xFF);


	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x34, ModeNo);

	return 1;
}
