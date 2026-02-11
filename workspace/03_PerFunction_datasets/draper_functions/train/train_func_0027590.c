falcon_xgxs_link_ok(struct efx_nic *efx)
{
	efx_oword_t reg;
	bool align_done, link_ok = false;
	int sync_status;


	efx_reado(efx, &reg, FR_AB_XX_CORE_STAT);

	align_done = EFX_OWORD_FIELD(reg, FRF_AB_XX_ALIGN_DONE);
	sync_status = EFX_OWORD_FIELD(reg, FRF_AB_XX_SYNC_STAT);
	if (align_done && (sync_status == FFE_AB_XX_STAT_ALL_LANES))
		link_ok = true;


	EFX_SET_OWORD_FIELD(reg, FRF_AB_XX_COMMA_DET, FFE_AB_XX_STAT_ALL_LANES);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_XX_CHAR_ERR, FFE_AB_XX_STAT_ALL_LANES);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_XX_DISPERR, FFE_AB_XX_STAT_ALL_LANES);
	efx_writeo(efx, &reg, FR_AB_XX_CORE_STAT);

	return link_ok;
}
