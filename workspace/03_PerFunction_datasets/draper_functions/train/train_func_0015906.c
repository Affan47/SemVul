efx_ef10_push_irq_moderation(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	unsigned int mode, value;
	efx_dword_t timer_cmd;

	if (channel->irq_moderation) {
		mode = 3;
		value = channel->irq_moderation - 1;
	} else {
		mode = 0;
		value = 0;
	}

	if (EFX_EF10_WORKAROUND_35388(efx)) {
		EFX_POPULATE_DWORD_3(timer_cmd, ERF_DD_EVQ_IND_TIMER_FLAGS,
				     EFE_DD_EVQ_IND_TIMER_FLAGS,
				     ERF_DD_EVQ_IND_TIMER_MODE, mode,
				     ERF_DD_EVQ_IND_TIMER_VAL, value);
		efx_writed_page(efx, &timer_cmd, ER_DD_EVQ_INDIRECT,
				channel->channel);
	} else {
		EFX_POPULATE_DWORD_2(timer_cmd, ERF_DZ_TC_TIMER_MODE, mode,
				     ERF_DZ_TC_TIMER_VAL, value);
		efx_writed_page(efx, &timer_cmd, ER_DZ_EVQ_TMR,
				channel->channel);
	}
}
