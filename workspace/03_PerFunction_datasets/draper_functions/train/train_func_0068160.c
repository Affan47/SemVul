falcon_reset_macs(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg, mac_ctrl;
	int count;

	if (efx_nic_rev(efx) < EFX_REV_FALCON_B0) {


		EFX_POPULATE_OWORD_1(reg, FRF_AB_XM_CORE_RST, 1);
		efx_writeo(efx, &reg, FR_AB_XM_GLB_CFG);

		for (count = 0; count < 10000; count++) {
			efx_reado(efx, &reg, FR_AB_XM_GLB_CFG);
			if (EFX_OWORD_FIELD(reg, FRF_AB_XM_CORE_RST) ==
			    0)
				return;
			udelay(10);
		}

		netif_err(efx, hw, efx->net_dev,
			  "timed out waiting for XMAC core reset\n");
	}


	WARN_ON(nic_data->stats_disable_count == 0);

	efx_reado(efx, &mac_ctrl, FR_AB_MAC_CTRL);
	EFX_SET_OWORD_FIELD(mac_ctrl, FRF_BB_TXFIFO_DRAIN_EN, 1);
	efx_writeo(efx, &mac_ctrl, FR_AB_MAC_CTRL);

	efx_reado(efx, &reg, FR_AB_GLB_CTL);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_RST_XGTX, 1);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_RST_XGRX, 1);
	EFX_SET_OWORD_FIELD(reg, FRF_AB_RST_EM, 1);
	efx_writeo(efx, &reg, FR_AB_GLB_CTL);

	count = 0;
	while (1) {
		efx_reado(efx, &reg, FR_AB_GLB_CTL);
		if (!EFX_OWORD_FIELD(reg, FRF_AB_RST_XGTX) &&
		    !EFX_OWORD_FIELD(reg, FRF_AB_RST_XGRX) &&
		    !EFX_OWORD_FIELD(reg, FRF_AB_RST_EM)) {
			netif_dbg(efx, hw, efx->net_dev,
				  "Completed MAC reset after %d loops\n",
				  count);
			break;
		}
		if (count > 20) {
			netif_err(efx, hw, efx->net_dev, "MAC reset failed\n");
			break;
		}
		count++;
		udelay(10);
	}


	efx_writeo(efx, &mac_ctrl, FR_AB_MAC_CTRL);

	falcon_setup_xaui(efx);
}
