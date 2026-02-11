bthci_AssocPALVer(struct rtw_adapter *padapter, void *pbuf)
{
	struct amp_assoc_structure *pAssoStrc = (struct amp_assoc_structure *)pbuf;
	u8 *pu1Tmp;
	u16	*pu2Tmp;

	pAssoStrc->TypeID = AMP_80211_PAL_VISION;
	pAssoStrc->Length = 0x5;
	pu1Tmp = &pAssoStrc->Data[0];
	*pu1Tmp = 0x1;
	pu2Tmp = (u16 *)&pAssoStrc->Data[1];
	*pu2Tmp = 0x5D;
	pu2Tmp = (u16 *)&pAssoStrc->Data[3];
	*pu2Tmp = 0x1;

	RTPRINT_DATA(FIOCTL, IOCTL_BT_HCICMD_DETAIL, ("AssocPALVer : \n"), pAssoStrc, pAssoStrc->Length+3);
	RTPRINT(FIOCTL, IOCTL_BT_LOGO, ("AssocPALVer \n"));

	RTPRINT(FIOCTL, IOCTL_BT_LOGO, (" TypeID = 0x%x,\n Length = 0x%x,\n PAL Version = 0x01,\n PAL vendor = 0x01,\n PAL Sub-version specifier = 0x01\n",
		pAssoStrc->TypeID,
		pAssoStrc->Length));
	return pAssoStrc->Length + 3;
}
