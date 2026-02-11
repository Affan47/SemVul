efx_farch_interrupts(struct efx_nic *efx,
				      bool enabled, bool force)
{
	efx_oword_t int_en_reg_ker;

	EFX_POPULATE_OWORD_3(int_en_reg_ker,
			     FRF_AZ_KER_INT_LEVE_SEL, efx->irq_level,
			     FRF_AZ_KER_INT_KER, force,
			     FRF_AZ_DRV_INT_EN_KER, enabled);
	efx_writeo(efx, &int_en_reg_ker, FR_AZ_INT_EN_KER);
}
