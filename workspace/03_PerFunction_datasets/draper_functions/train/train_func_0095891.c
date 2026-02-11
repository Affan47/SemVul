_PageWrite(struct rtw_adapter *padapter, u32 page, void *buffer, u32 size)
{
	u8 value8;
	u8 u8Page = (u8) (page & 0x07);

	if (size > MAX_PAGE_SIZE)
		return _FAIL;

	value8 = (rtl8723au_read8(padapter, REG_MCUFWDL + 2) & 0xF8) | u8Page;
	rtl8723au_write8(padapter, REG_MCUFWDL + 2, value8);

	return rtl8723au_writeN(padapter, FW_8723A_START_ADDRESS, size, buffer);
}
