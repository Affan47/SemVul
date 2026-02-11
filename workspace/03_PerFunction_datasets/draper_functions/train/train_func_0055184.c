FindMinimumRSSI(struct rtw_adapter *pAdapter)
{
	struct hal_data_8723a *pHalData = GET_HAL_DATA(pAdapter);
	struct dm_priv *pdmpriv = &pHalData->dmpriv;
	struct dm_odm_t *pDM_Odm = &pHalData->odmpriv;


	if (!pDM_Odm->bLinked && !pdmpriv->EntryMinUndecoratedSmoothedPWDB)
		pdmpriv->MinUndecoratedPWDBForDM = 0;
	else
		pdmpriv->MinUndecoratedPWDBForDM =
			pdmpriv->EntryMinUndecoratedSmoothedPWDB;
}
