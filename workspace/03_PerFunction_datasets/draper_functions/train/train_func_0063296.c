efx_soft_disable_interrupts(struct efx_nic *efx)
{
	struct efx_channel *channel;

	if (efx->state == STATE_DISABLED)
		return;

	efx_mcdi_mode_poll(efx);

	efx->irq_soft_enabled = false;
	smp_wmb();

	if (efx->legacy_irq)
		synchronize_irq(efx->legacy_irq);

	efx_for_each_channel(channel, efx) {
		if (channel->irq)
			synchronize_irq(channel->irq);

		efx_stop_eventq(channel);
		if (!channel->type->keep_eventq)
			efx_fini_eventq(channel);
	}


	efx_mcdi_flush_async(efx);
}
