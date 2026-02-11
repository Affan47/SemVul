SiS_GetRatePtr(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
	       unsigned short ModeIdIndex)
{
	unsigned short rrti, i, index, temp;

	if (ModeNo <= 0x13)
		return 0xFFFF;

	index = SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x33) & 0x0F;
	if (index > 0)
		index--;

	rrti = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
	ModeNo = SiS_Pr->SiS_RefIndex[rrti].ModeID;

	i = 0;
	do {
		if (SiS_Pr->SiS_RefIndex[rrti + i].ModeID != ModeNo)
			break;

		temp =
		    SiS_Pr->SiS_RefIndex[rrti + i].Ext_InfoFlag & ModeTypeMask;
		if (temp < SiS_Pr->SiS_ModeType)
			break;

		i++;
		index--;
	} while (index != 0xFFFF);

	i--;

	return (rrti + i);
}
