dwc2_set_parameters(struct dwc2_hsotg *hsotg,
			 const struct dwc2_core_params *params)
{
	dev_dbg(hsotg->dev, "%s()\n", __func__);

	dwc2_set_param_otg_cap(hsotg, params->otg_cap);
	dwc2_set_param_dma_enable(hsotg, params->dma_enable);
	dwc2_set_param_dma_desc_enable(hsotg, params->dma_desc_enable);
	dwc2_set_param_host_support_fs_ls_low_power(hsotg,
			params->host_support_fs_ls_low_power);
	dwc2_set_param_enable_dynamic_fifo(hsotg,
			params->enable_dynamic_fifo);
	dwc2_set_param_host_rx_fifo_size(hsotg,
			params->host_rx_fifo_size);
	dwc2_set_param_host_nperio_tx_fifo_size(hsotg,
			params->host_nperio_tx_fifo_size);
	dwc2_set_param_host_perio_tx_fifo_size(hsotg,
			params->host_perio_tx_fifo_size);
	dwc2_set_param_max_transfer_size(hsotg,
			params->max_transfer_size);
	dwc2_set_param_max_packet_count(hsotg,
			params->max_packet_count);
	dwc2_set_param_host_channels(hsotg, params->host_channels);
	dwc2_set_param_phy_type(hsotg, params->phy_type);
	dwc2_set_param_speed(hsotg, params->speed);
	dwc2_set_param_host_ls_low_power_phy_clk(hsotg,
			params->host_ls_low_power_phy_clk);
	dwc2_set_param_phy_ulpi_ddr(hsotg, params->phy_ulpi_ddr);
	dwc2_set_param_phy_ulpi_ext_vbus(hsotg,
			params->phy_ulpi_ext_vbus);
	dwc2_set_param_phy_utmi_width(hsotg, params->phy_utmi_width);
	dwc2_set_param_ulpi_fs_ls(hsotg, params->ulpi_fs_ls);
	dwc2_set_param_ts_dline(hsotg, params->ts_dline);
	dwc2_set_param_i2c_enable(hsotg, params->i2c_enable);
	dwc2_set_param_en_multiple_tx_fifo(hsotg,
			params->en_multiple_tx_fifo);
	dwc2_set_param_reload_ctl(hsotg, params->reload_ctl);
	dwc2_set_param_ahbcfg(hsotg, params->ahbcfg);
	dwc2_set_param_otg_ver(hsotg, params->otg_ver);
	dwc2_set_param_uframe_sched(hsotg, params->uframe_sched);
	dwc2_set_param_external_id_pin_ctl(hsotg, params->external_id_pin_ctl);
	dwc2_set_param_hibernation(hsotg, params->hibernation);
}
