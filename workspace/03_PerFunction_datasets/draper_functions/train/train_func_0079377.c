SiS_SetCRT1FIFO_310(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		    unsigned short mi)
{
	unsigned short modeflag = SiS_Pr->SiS_EModeIDTable[mi].Ext_ModeFlag;


	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x3D, 0xFE);

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x08, 0xAE);
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x09, 0xF0);

	if (ModeNo <= 0x13)
		return;

	if ((!(modeflag & DoubleScanMode)) || (!(modeflag & HalfDCLK))) {
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x08, 0x34);
		SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x3D, 0x01);
	}
}
