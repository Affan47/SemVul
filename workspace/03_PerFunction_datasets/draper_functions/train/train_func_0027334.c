efx_farch_ev_read_ack(struct efx_channel *channel)
{
	efx_dword_t reg;
	struct efx_nic *efx = channel->efx;

	EFX_POPULATE_DWORD_1(reg, FRF_AZ_EVQ_RPTR,
			     channel->eventq_read_ptr & channel->eventq_mask);


	efx_writed(efx, &reg,
		   efx->type->evq_rptr_tbl_base +
		   FR_BZ_EVQ_RPTR_STEP * channel->channel);
}
