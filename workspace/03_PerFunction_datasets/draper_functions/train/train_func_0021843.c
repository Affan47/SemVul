set_local_link_attributes(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u8 enable_lane_tx;
	u8 tx_polarity_inversion;
	u8 rx_polarity_inversion;
	int ret;


	fabric_serdes_reset(dd);


	ret = read_tx_settings(dd, &enable_lane_tx, &tx_polarity_inversion,
		&rx_polarity_inversion, &ppd->local_tx_rate);
	if (ret)
		goto set_local_link_attributes_fail;

	if (dd->dc8051_ver < dc8051_ver(0, 20)) {

		if (ppd->link_speed_enabled & OPA_LINK_SPEED_25G)
			ppd->local_tx_rate = 1;
		else
			ppd->local_tx_rate = 0;
	} else {

		ppd->local_tx_rate = 0;
		if (ppd->link_speed_enabled & OPA_LINK_SPEED_25G)
			ppd->local_tx_rate |= 2;
		if (ppd->link_speed_enabled & OPA_LINK_SPEED_12_5G)
			ppd->local_tx_rate |= 1;
	}

	enable_lane_tx = 0xF;
	ret = write_tx_settings(dd, enable_lane_tx, tx_polarity_inversion,
		     rx_polarity_inversion, ppd->local_tx_rate);
	if (ret != HCMD_SUCCESS)
		goto set_local_link_attributes_fail;


	ret = write_vc_local_phy(dd, 0 ,
				     1 );
	if (ret != HCMD_SUCCESS)
		goto set_local_link_attributes_fail;


	ret = write_vc_local_fabric(dd, dd->vau, 1, dd->vcu, dd->vl15_init,
				    ppd->port_crc_mode_enabled);
	if (ret != HCMD_SUCCESS)
		goto set_local_link_attributes_fail;

	ret = write_vc_local_link_width(dd, 0, 0,
		     opa_to_vc_link_widths(ppd->link_width_enabled));
	if (ret != HCMD_SUCCESS)
		goto set_local_link_attributes_fail;


	ret = write_local_device_id(dd, dd->pcidev->device, dd->minrev);
	if (ret == HCMD_SUCCESS)
		return 0;

set_local_link_attributes_fail:
	dd_dev_err(dd,
		"Failed to set local link attributes, return 0x%x\n",
		ret);
	return ret;
}
