_PHY_PathA_IQK(struct rtw_adapter *pAdapter, bool configPathB)
{
	u32 regEAC, regE94, regE9C, regEA4;
	u8 result = 0x00;
	struct hal_data_8723a *pHalData = GET_HAL_DATA(pAdapter);


	rtl8723au_write32(pAdapter, rTx_IQK_Tone_A, 0x10008c1f);
	rtl8723au_write32(pAdapter, rRx_IQK_Tone_A, 0x10008c1f);
	rtl8723au_write32(pAdapter, rTx_IQK_PI_A, 0x82140102);

	rtl8723au_write32(pAdapter, rRx_IQK_PI_A, configPathB ? 0x28160202 :
		IS_81xxC_VENDOR_UMC_B_CUT(pHalData->VersionID)?0x28160202:0x28160502);


	if (configPathB) {
		rtl8723au_write32(pAdapter, rTx_IQK_Tone_B, 0x10008c22);
		rtl8723au_write32(pAdapter, rRx_IQK_Tone_B, 0x10008c22);
		rtl8723au_write32(pAdapter, rTx_IQK_PI_B, 0x82140102);
		rtl8723au_write32(pAdapter, rRx_IQK_PI_B, 0x28160202);
	}


	rtl8723au_write32(pAdapter, rIQK_AGC_Rsp, 0x001028d1);


	rtl8723au_write32(pAdapter, rIQK_AGC_Pts, 0xf9000000);
	rtl8723au_write32(pAdapter, rIQK_AGC_Pts, 0xf8000000);


	udelay(IQK_DELAY_TIME*1000);


	regEAC = rtl8723au_read32(pAdapter, rRx_Power_After_IQK_A_2);
	regE94 = rtl8723au_read32(pAdapter, rTx_Power_Before_IQK_A);
	regE9C = rtl8723au_read32(pAdapter, rTx_Power_After_IQK_A);
	regEA4 = rtl8723au_read32(pAdapter, rRx_Power_Before_IQK_A_2);

	if (!(regEAC & BIT(28)) &&
	    (((regE94 & 0x03FF0000)>>16) != 0x142) &&
	    (((regE9C & 0x03FF0000)>>16) != 0x42))
		result |= 0x01;
	else
		return result;

	if (!(regEAC & BIT(27)) &&
	    (((regEA4 & 0x03FF0000)>>16) != 0x132) &&
	    (((regEAC & 0x03FF0000)>>16) != 0x36))
		result |= 0x02;
	else
		DBG_8723A("Path A Rx IQK fail!!\n");
	return result;
}
