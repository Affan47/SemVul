Tspi_PcrComposite_SetPcrLocality(TSS_HPCRS hPcrComposite,
				 UINT32    LocalityValue)
{

	if (!LocalityValue || (LocalityValue & (~TSS_LOCALITY_ALL)))
		return TSPERR(TSS_E_BAD_PARAMETER);

	return obj_pcrs_set_locality(hPcrComposite, LocalityValue);
}
