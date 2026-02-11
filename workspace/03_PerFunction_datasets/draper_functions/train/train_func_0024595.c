qt202x_phy_reconfigure(struct efx_nic *efx)
{
	struct qt202x_phy_data *phy_data = efx->phy_data;

	if (efx->phy_type == PHY_TYPE_QT2025C) {
		int rc = qt2025c_select_phy_mode(efx);
		if (rc)
			return rc;


		mdio_set_flag(
			&efx->mdio, efx->mdio.prtad, MDIO_MMD_PMAPMD,
			PMA_PMD_FTX_CTRL2_REG, 1 << PMA_PMD_FTX_STATIC_LBN,
			efx->phy_mode & PHY_MODE_TX_DISABLED ||
			efx->phy_mode & PHY_MODE_LOW_POWER ||
			efx->loopback_mode == LOOPBACK_PCS ||
			efx->loopback_mode == LOOPBACK_PMAPMD);
	} else {

		if (!(efx->phy_mode & PHY_MODE_TX_DISABLED) &&
		    (phy_data->phy_mode & PHY_MODE_TX_DISABLED))
			qt202x_reset_phy(efx);

		efx_mdio_transmit_disable(efx);
	}

	efx_mdio_phy_reconfigure(efx);

	phy_data->phy_mode = efx->phy_mode;

	return 0;
}
