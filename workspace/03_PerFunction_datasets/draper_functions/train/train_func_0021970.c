be_set_vf_tx_rate(struct net_device *netdev, int vf,
			     int min_tx_rate, int max_tx_rate)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct device *dev = &adapter->pdev->dev;
	int percent_rate, status = 0;
	u16 link_speed = 0;
	u8 link_status;

	if (!sriov_enabled(adapter))
		return -EPERM;

	if (vf >= adapter->num_vfs)
		return -EINVAL;

	if (min_tx_rate)
		return -EINVAL;

	if (!max_tx_rate)
		goto config_qos;

	status = be_cmd_link_status_query(adapter, &link_speed,
					  &link_status, 0);
	if (status)
		goto err;

	if (!link_status) {
		dev_err(dev, "TX-rate setting not allowed when link is down\n");
		status = -ENETDOWN;
		goto err;
	}

	if (max_tx_rate < 100 || max_tx_rate > link_speed) {
		dev_err(dev, "TX-rate must be between 100 and %d Mbps\n",
			link_speed);
		status = -EINVAL;
		goto err;
	}


	percent_rate = link_speed / 100;
	if (skyhawk_chip(adapter) && (max_tx_rate % percent_rate)) {
		dev_err(dev, "TX-rate must be a multiple of %d Mbps\n",
			percent_rate);
		status = -EINVAL;
		goto err;
	}

config_qos:
	status = be_cmd_config_qos(adapter, max_tx_rate, link_speed, vf + 1);
	if (status)
		goto err;

	adapter->vf_cfg[vf].tx_rate = max_tx_rate;
	return 0;

err:
	dev_err(dev, "TX-rate setting of %dMbps on VF%d failed\n",
		max_tx_rate, vf);
	return be_cmd_status(status);
}
