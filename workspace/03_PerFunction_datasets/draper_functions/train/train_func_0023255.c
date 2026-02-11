prism54_debug_get_oid(struct net_device *ndev, struct iw_request_info *info,
		      struct iw_point *data, char *extra)
{
	islpci_private *priv = netdev_priv(ndev);
	struct islpci_mgmtframe *response;
	int ret = -EIO;

	printk("%s: get_oid 0x%08X\n", ndev->name, priv->priv_oid);
	data->length = 0;

	if (islpci_get_state(priv) >= PRV_STATE_INIT) {
		ret =
		    islpci_mgt_transaction(priv->ndev, PIMFOR_OP_GET,
					   priv->priv_oid, extra, 256,
					   &response);
		printk("%s: ret: %i\n", ndev->name, ret);
		if (ret || !response
		    || response->header->operation == PIMFOR_OP_ERROR) {
			if (response) {
				islpci_mgt_release(response);
			}
			printk("%s: EIO\n", ndev->name);
			ret = -EIO;
		}
		if (!ret) {
			data->length = response->header->length;
			memcpy(extra, response->data, data->length);
			islpci_mgt_release(response);
			printk("%s: len: %i\n", ndev->name, data->length);
		}
	}

	return ret;
}
