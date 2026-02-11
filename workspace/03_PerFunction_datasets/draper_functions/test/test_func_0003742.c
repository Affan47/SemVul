rtl8723a_dual_antenna_detection(struct rtw_adapter *padapter)
{
	struct hal_data_8723a *pHalData;
	struct dm_odm_t *pDM_Odm;
	struct sw_ant_sw *pDM_SWAT_Table;
	u8 i;

	pHalData = GET_HAL_DATA(padapter);
	pDM_Odm = &pHalData->odmpriv;
	pDM_SWAT_Table = &pDM_Odm->DM_SWAT_Table;


	if (!pHalData->bAntennaDetected) {
		u8 btAntNum = BT_GetPGAntNum(padapter);


		if (btAntNum == Ant_x2)
			pDM_SWAT_Table->ANTB_ON = true;
		else if (btAntNum == Ant_x1)
			pDM_SWAT_Table->ANTB_ON = false;
		else
			pDM_SWAT_Table->ANTB_ON = true;

		if (pHalData->CustomerID != RT_CID_TOSHIBA) {
			for (i = 0; i < MAX_ANTENNA_DETECTION_CNT; i++) {
				if (ODM_SingleDualAntennaDetection
				    (&pHalData->odmpriv, ANTTESTALL) == true)
					break;
			}


			if (btAntNum == Ant_x2)
				BT_SetBtCoexCurrAntNum(padapter,
						       pDM_SWAT_Table->
						       ANTB_ON ? 2 : 1);
		}
		pHalData->bAntennaDetected = true;
	}
}
