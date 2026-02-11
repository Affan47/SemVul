cdc_mbim_bind(struct usbnet *dev, struct usb_interface *intf)
{
	struct cdc_ncm_ctx *ctx;
	struct usb_driver *subdriver = ERR_PTR(-ENODEV);
	int ret = -ENODEV;
	u8 data_altsetting = 1;
	struct cdc_mbim_state *info = (void *)&dev->data;


	if (cdc_ncm_select_altsetting(intf) == CDC_NCM_COMM_ALTSETTING_MBIM) {
		data_altsetting = CDC_NCM_DATA_ALTSETTING_MBIM;
		ret = cdc_mbim_set_ctrlalt(dev, intf, CDC_NCM_COMM_ALTSETTING_MBIM);
		if (ret)
			goto err;
		ret = -ENODEV;
	}


	if (!cdc_ncm_comm_intf_is_mbim(intf->cur_altsetting))
		goto err;

	ret = cdc_ncm_bind_common(dev, intf, data_altsetting, dev->driver_info->data);
	if (ret)
		goto err;

	ctx = info->ctx;


	if (ctx->mbim_desc && dev->status)
		subdriver = usb_cdc_wdm_register(ctx->control,
						 &dev->status->desc,
						 le16_to_cpu(ctx->mbim_desc->wMaxControlMessage),
						 cdc_mbim_wdm_manage_power);
	if (IS_ERR(subdriver)) {
		ret = PTR_ERR(subdriver);
		cdc_ncm_unbind(dev, intf);
		goto err;
	}


	dev->status = NULL;
	info->subdriver = subdriver;


	dev->net->flags |= IFF_NOARP;


	dev->net->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_FILTER;


	dev->net->netdev_ops = &cdc_mbim_netdev_ops;
err:
	return ret;
}
