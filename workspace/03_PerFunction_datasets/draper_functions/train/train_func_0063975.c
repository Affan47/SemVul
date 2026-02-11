ql_init_fw_done(struct ql_adapter *qdev, struct mbox_params *mbcp)
{
	int status;

	mbcp->out_count = 2;

	status = ql_get_mb_sts(qdev, mbcp);
	if (status) {
		netif_err(qdev, drv, qdev->ndev, "Firmware did not initialize!\n");
	} else {
		netif_err(qdev, drv, qdev->ndev, "Firmware Revision  = 0x%.08x.\n",
			  mbcp->mbox_out[1]);
		qdev->fw_rev_id = mbcp->mbox_out[1];
		status = ql_cam_route_initialize(qdev);
		if (status)
			netif_err(qdev, ifup, qdev->ndev,
				  "Failed to init CAM/Routing tables.\n");
	}
}
