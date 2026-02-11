efx_probe_all(struct efx_nic *efx)
{
	int rc;

	rc = efx_probe_nic(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to create NIC\n");
		goto fail1;
	}

	rc = efx_probe_port(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to create port\n");
		goto fail2;
	}

	BUILD_BUG_ON(EFX_DEFAULT_DMAQ_SIZE < EFX_RXQ_MIN_ENT);
	if (WARN_ON(EFX_DEFAULT_DMAQ_SIZE < EFX_TXQ_MIN_ENT(efx))) {
		rc = -EINVAL;
		goto fail3;
	}
	efx->rxq_entries = efx->txq_entries = EFX_DEFAULT_DMAQ_SIZE;

#ifdef CONFIG_SFC_SRIOV
	rc = efx->type->vswitching_probe(efx);
	if (rc)
		netif_warn(efx, probe, efx->net_dev,
			   "failed to setup vswitching rc=%d;"
			   " VFs may not function\n", rc);
#endif

	rc = efx_probe_filters(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "failed to create filter tables\n");
		goto fail4;
	}

	rc = efx_probe_channels(efx);
	if (rc)
		goto fail5;

	return 0;

 fail5:
	efx_remove_filters(efx);
 fail4:
#ifdef CONFIG_SFC_SRIOV
	efx->type->vswitching_remove(efx);
#endif
 fail3:
	efx_remove_port(efx);
 fail2:
	efx_remove_nic(efx);
 fail1:
	return rc;
}
