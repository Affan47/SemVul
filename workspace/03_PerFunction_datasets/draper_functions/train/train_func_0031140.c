efx_ptp_remove(struct efx_nic *efx)
{
	if (!efx->ptp_data)
		return;

	(void)efx_ptp_disable(efx);

	cancel_work_sync(&efx->ptp_data->work);
	cancel_work_sync(&efx->ptp_data->pps_work);

	skb_queue_purge(&efx->ptp_data->rxq);
	skb_queue_purge(&efx->ptp_data->txq);

	if (efx->ptp_data->phc_clock) {
		destroy_workqueue(efx->ptp_data->pps_workwq);
		ptp_clock_unregister(efx->ptp_data->phc_clock);
	}

	destroy_workqueue(efx->ptp_data->workwq);

	efx_nic_free_buffer(efx, &efx->ptp_data->start);
	kfree(efx->ptp_data);
}
