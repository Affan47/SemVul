SiS_SetVCLKState(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		 unsigned short rrti)
{
	unsigned short data = 0, VCLK = 0, index = 0;

	if (ModeNo > 0x13) {
		index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRTVCLK;
		VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;
	}

	if (VCLK >= 166)
		data |= 0x0c;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x32, 0xf3, data);

	if (VCLK >= 166)
		SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1f, 0xe7);


	data = 0x03;
	if (VCLK >= 260)
		data = 0x00;
	else if (VCLK >= 160)
		data = 0x01;
	else if (VCLK >= 135)
		data = 0x02;

	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x07, 0xF8, data);
}
