efx_farch_ev_init(struct efx_channel *channel)
{
	efx_oword_t reg;
	struct efx_nic *efx = channel->efx;

	netif_dbg(efx, hw, efx->net_dev,
		  "channel %d event queue in special buffers %d-%d\n",
		  channel->channel, channel->eventq.index,
		  channel->eventq.index + channel->eventq.entries - 1);

	if (efx_nic_rev(efx) >= EFX_REV_SIENA_A0) {
		EFX_POPULATE_OWORD_3(reg,
				     FRF_CZ_TIMER_Q_EN, 1,
				     FRF_CZ_HOST_NOTIFY_MODE, 0,
				     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
		efx_writeo_table(efx, &reg, FR_BZ_TIMER_TBL, channel->channel);
	}


	efx_init_special_buffer(efx, &channel->eventq);


	memset(channel->eventq.buf.addr, 0xff, channel->eventq.buf.len);


	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(channel->eventq.entries),
			     FRF_AZ_EVQ_BUF_BASE_ID, channel->eventq.index);
	efx_writeo_table(efx, &reg, efx->type->evq_ptr_tbl_base,
			 channel->channel);

	return 0;
}
