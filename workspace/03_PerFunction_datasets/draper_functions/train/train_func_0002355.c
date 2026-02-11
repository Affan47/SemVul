bnxt_sriov_enable(struct bnxt *bp, int *num_vfs)
{
	int rc = 0, vfs_supported;
	int min_rx_rings, min_tx_rings, min_rss_ctxs;
	int tx_ok = 0, rx_ok = 0, rss_ok = 0;


	vfs_supported = *num_vfs;

	while (vfs_supported) {
		min_rx_rings = vfs_supported;
		min_tx_rings = vfs_supported;
		min_rss_ctxs = vfs_supported;

		if (bp->flags & BNXT_FLAG_AGG_RINGS) {
			if (bp->pf.max_rx_rings - bp->rx_nr_rings * 2 >=
			    min_rx_rings)
				rx_ok = 1;
		} else {
			if (bp->pf.max_rx_rings - bp->rx_nr_rings >=
			    min_rx_rings)
				rx_ok = 1;
		}
		if (bp->pf.max_vnics - bp->nr_vnics < min_rx_rings)
			rx_ok = 0;

		if (bp->pf.max_tx_rings - bp->tx_nr_rings >= min_tx_rings)
			tx_ok = 1;

		if (bp->pf.max_rsscos_ctxs - bp->rsscos_nr_ctxs >= min_rss_ctxs)
			rss_ok = 1;

		if (tx_ok && rx_ok && rss_ok)
			break;

		vfs_supported--;
	}

	if (!vfs_supported) {
		netdev_err(bp->dev, "Cannot enable VF's as all resources are used by PF\n");
		return -EINVAL;
	}

	if (vfs_supported != *num_vfs) {
		netdev_info(bp->dev, "Requested VFs %d, can enable %d\n",
			    *num_vfs, vfs_supported);
		*num_vfs = vfs_supported;
	}

	rc = bnxt_alloc_vf_resources(bp, *num_vfs);
	if (rc)
		goto err_out1;


	rc = bnxt_hwrm_func_cfg(bp, *num_vfs);
	if (rc)
		goto err_out2;


	rc = bnxt_hwrm_func_buf_rgtr(bp);
	if (rc)
		goto err_out2;

	bnxt_ulp_sriov_cfg(bp, *num_vfs);

	rc = pci_enable_sriov(bp->pdev, *num_vfs);
	if (rc)
		goto err_out2;

	return 0;

err_out2:

	bnxt_hwrm_func_vf_resource_free(bp, *num_vfs);

err_out1:
	bnxt_free_vf_resources(bp);

	return rc;
}
