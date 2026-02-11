odm_RSSIMonitorCheck(struct dm_odm_t *pDM_Odm)
{
	struct rtw_adapter *Adapter = pDM_Odm->Adapter;
	struct hal_data_8723a *pHalData = GET_HAL_DATA(Adapter);
	struct dm_priv *pdmpriv = &pHalData->dmpriv;
	int i;
	int MaxDB = 0, MinDB = 0xff;
	u8 sta_cnt = 0;
	u32 tmpdb;
	u32 PWDB_rssi[NUM_STA] = {0};
	struct sta_info *psta;

	if (!pDM_Odm->bLinked)
		return;

	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) {
		psta = pDM_Odm->pODM_StaInfo[i];
		if (psta) {
			if (psta->rssi_stat.UndecoratedSmoothedPWDB < MinDB)
				MinDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

			if (psta->rssi_stat.UndecoratedSmoothedPWDB > MaxDB)
				MaxDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

			if (psta->rssi_stat.UndecoratedSmoothedPWDB != -1) {
				tmpdb = psta->rssi_stat.UndecoratedSmoothedPWDB;
				PWDB_rssi[sta_cnt++] = psta->mac_id |
					(tmpdb << 16);
			}
		}
	}

	for (i = 0; i < sta_cnt; i++) {
		if (PWDB_rssi[i] != (0))
			rtl8723a_set_rssi_cmd(Adapter, (u8 *)&PWDB_rssi[i]);
	}

	pdmpriv->EntryMaxUndecoratedSmoothedPWDB = MaxDB;

	if (MinDB != 0xff)
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = MinDB;
	else
		pdmpriv->EntryMinUndecoratedSmoothedPWDB = 0;

	FindMinimumRSSI(Adapter);

	ODM_CmnInfoUpdate23a(&pHalData->odmpriv, ODM_CMNINFO_RSSI_MIN,
			     pdmpriv->MinUndecoratedPWDBForDM);
}
