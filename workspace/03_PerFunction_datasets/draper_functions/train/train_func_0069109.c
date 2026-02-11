efx_mcdi_nvram_test_all(struct efx_nic *efx)
{
	u32 nvram_types;
	unsigned int type;
	int rc;

	rc = efx_mcdi_nvram_types(efx, &nvram_types);
	if (rc)
		goto fail1;

	type = 0;
	while (nvram_types != 0) {
		if (nvram_types & 1) {
			rc = efx_mcdi_nvram_test(efx, type);
			if (rc)
				goto fail2;
		}
		type++;
		nvram_types >>= 1;
	}

	return 0;

fail2:
	netif_err(efx, hw, efx->net_dev, "%s: failed type=%u\n",
		  __func__, type);
fail1:
	netif_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
	return rc;
}
