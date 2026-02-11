efx_nic_fini_interrupt(struct efx_nic *efx)
{
	struct efx_channel *channel;

#ifdef CONFIG_RFS_ACCEL
	free_irq_cpu_rmap(efx->net_dev->rx_cpu_rmap);
	efx->net_dev->rx_cpu_rmap = NULL;
#endif

	if (EFX_INT_MODE_USE_MSI(efx)) {

		efx_for_each_channel(channel, efx)
			free_irq(channel->irq,
				 &efx->msi_context[channel->channel]);
	} else {

		free_irq(efx->legacy_irq, efx);
	}
}
