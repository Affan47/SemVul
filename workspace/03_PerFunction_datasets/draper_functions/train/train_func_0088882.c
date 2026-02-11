hal_EfuseSwitchToBank(struct rtw_adapter *padapter, u8 bank)
{
	u8 bRet = false;
	u32 value32 = 0;

	DBG_8723A("%s: Efuse switch bank to %d\n", __func__, bank);
	value32 = rtl8723au_read32(padapter, EFUSE_TEST);
	bRet = true;
	switch (bank) {
	case 0:
		value32 = (value32 & ~EFUSE_SEL_MASK) |
			EFUSE_SEL(EFUSE_WIFI_SEL_0);
		break;
	case 1:
		value32 = (value32 & ~EFUSE_SEL_MASK) |
			EFUSE_SEL(EFUSE_BT_SEL_0);
		break;
	case 2:
		value32 = (value32 & ~EFUSE_SEL_MASK) |
			EFUSE_SEL(EFUSE_BT_SEL_1);
		break;
	case 3:
		value32 = (value32 & ~EFUSE_SEL_MASK) |
			EFUSE_SEL(EFUSE_BT_SEL_2);
		break;
	default:
		value32 = (value32 & ~EFUSE_SEL_MASK) |
			EFUSE_SEL(EFUSE_WIFI_SEL_0);
		bRet = false;
		break;
	}
	rtl8723au_write32(padapter, EFUSE_TEST, value32);

	return bRet;
}
