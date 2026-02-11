efx_ptp_insert_multicast_filters(struct efx_nic *efx)
{
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct efx_filter_spec rxfilter;
	int rc;

	if (!ptp->channel || ptp->rxfilter_installed)
		return 0;


	efx_filter_init_rx(&rxfilter, EFX_FILTER_PRI_REQUIRED, 0,
			   efx_rx_queue_index(
				   efx_channel_get_rx_queue(ptp->channel)));
	rc = efx_filter_set_ipv4_local(&rxfilter, IPPROTO_UDP,
				       htonl(PTP_ADDRESS),
				       htons(PTP_EVENT_PORT));
	if (rc != 0)
		return rc;

	rc = efx_filter_insert_filter(efx, &rxfilter, true);
	if (rc < 0)
		return rc;
	ptp->rxfilter_event = rc;

	efx_filter_init_rx(&rxfilter, EFX_FILTER_PRI_REQUIRED, 0,
			   efx_rx_queue_index(
				   efx_channel_get_rx_queue(ptp->channel)));
	rc = efx_filter_set_ipv4_local(&rxfilter, IPPROTO_UDP,
				       htonl(PTP_ADDRESS),
				       htons(PTP_GENERAL_PORT));
	if (rc != 0)
		goto fail;

	rc = efx_filter_insert_filter(efx, &rxfilter, true);
	if (rc < 0)
		goto fail;
	ptp->rxfilter_general = rc;

	ptp->rxfilter_installed = true;
	return 0;

fail:
	efx_filter_remove_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
				  ptp->rxfilter_event);
	return rc;
}
