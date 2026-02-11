sfe4001_init(struct efx_nic *efx)
{
	struct falcon_board *board = falcon_board(efx);
	int rc;

#if defined(CONFIG_SENSORS_LM90) || defined(CONFIG_SENSORS_LM90_MODULE)
	board->hwmon_client =
		i2c_new_device(&board->i2c_adap, &sfe4001_hwmon_info);
#else
	board->hwmon_client =
		i2c_new_dummy(&board->i2c_adap, sfe4001_hwmon_info.addr);
#endif
	if (!board->hwmon_client)
		return -EIO;


	rc = i2c_smbus_write_byte_data(board->hwmon_client,
				       MAX664X_REG_WLHO, 90);
	if (rc)
		goto fail_hwmon;

	board->ioexp_client = i2c_new_dummy(&board->i2c_adap, PCA9539);
	if (!board->ioexp_client) {
		rc = -EIO;
		goto fail_hwmon;
	}

	if (efx->phy_mode & PHY_MODE_SPECIAL) {


		falcon_stop_nic_stats(efx);
	}
	rc = sfe4001_poweron(efx);
	if (rc)
		goto fail_ioexp;

	rc = device_create_file(&efx->pci_dev->dev, &dev_attr_phy_flash_cfg);
	if (rc)
		goto fail_on;

	netif_info(efx, hw, efx->net_dev, "PHY is powered on\n");
	return 0;

fail_on:
	sfe4001_poweroff(efx);
fail_ioexp:
	i2c_unregister_device(board->ioexp_client);
fail_hwmon:
	i2c_unregister_device(board->hwmon_client);
	return rc;
}
