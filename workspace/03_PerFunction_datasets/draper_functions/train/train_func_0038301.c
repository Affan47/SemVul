netvsc_change_mtu(struct net_device *ndev, int mtu)
{
	struct net_device_context *ndevctx = netdev_priv(ndev);
	struct netvsc_device *nvdev = ndevctx->nvdev;
	struct hv_device *hdev = ndevctx->device_ctx;
	struct netvsc_device_info device_info;
	int limit = ETH_DATA_LEN;
	u32 num_chn;
	int ret = 0;

	if (ndevctx->start_remove || !nvdev || nvdev->destroy)
		return -ENODEV;

	if (nvdev->nvsp_version >= NVSP_PROTOCOL_VERSION_2)
		limit = NETVSC_MTU - ETH_HLEN;

	if (mtu < NETVSC_MTU_MIN || mtu > limit)
		return -EINVAL;

	ret = netvsc_close(ndev);
	if (ret)
		goto out;

	num_chn = nvdev->num_chn;

	ndevctx->start_remove = true;
	rndis_filter_device_remove(hdev);

	ndev->mtu = mtu;

	memset(&device_info, 0, sizeof(device_info));
	device_info.ring_size = ring_size;
	device_info.num_chn = num_chn;
	device_info.max_num_vrss_chns = max_num_vrss_chns;
	rndis_filter_device_add(hdev, &device_info);

out:
	netvsc_open(ndev);
	ndevctx->start_remove = false;


	schedule_delayed_work(&ndevctx->dwork, 0);

	return ret;
}
