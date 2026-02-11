odm_TXPowerTrackingInit(struct dm_odm_t *pDM_Odm)
{
	struct rtw_adapter *Adapter = pDM_Odm->Adapter;
	struct hal_data_8723a *pHalData = GET_HAL_DATA(Adapter);
	struct dm_priv *pdmpriv = &pHalData->dmpriv;

	pdmpriv->bTXPowerTracking = true;
	pdmpriv->TXPowercount = 0;
	pdmpriv->bTXPowerTrackingInit = false;
	pdmpriv->TxPowerTrackControl = true;
	MSG_8723A("pdmpriv->TxPowerTrackControl = %d\n",
		  pdmpriv->TxPowerTrackControl);

	pDM_Odm->RFCalibrateInfo.TxPowerTrackControl = true;
}
