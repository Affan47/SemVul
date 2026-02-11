amd_handle_event(struct amd_ntb_dev *ndev, int vec)
{
	void __iomem *mmio = ndev->self_mmio;
	u32 status;

	status = readl(mmio + AMD_INTSTAT_OFFSET);
	if (!(status & AMD_EVENT_INTMASK))
		return;

	dev_dbg(ndev_dev(ndev), "status = 0x%x and vec = %d\n", status, vec);

	status &= AMD_EVENT_INTMASK;
	switch (status) {
	case AMD_PEER_FLUSH_EVENT:
		dev_info(ndev_dev(ndev), "Flush is done.\n");
		break;
	case AMD_PEER_RESET_EVENT:
		amd_ack_smu(ndev, AMD_PEER_RESET_EVENT);


		ntb_link_event(&ndev->ntb);

		schedule_delayed_work(&ndev->hb_timer, AMD_LINK_HB_TIMEOUT);

		break;
	case AMD_PEER_D3_EVENT:
	case AMD_PEER_PMETO_EVENT:
		amd_ack_smu(ndev, status);


		ntb_link_event(&ndev->ntb);

		break;
	case AMD_PEER_D0_EVENT:
		mmio = ndev->peer_mmio;
		status = readl(mmio + AMD_PMESTAT_OFFSET);

		if (status & 0x1)
			dev_info(ndev_dev(ndev), "Wakeup is done.\n");

		amd_ack_smu(ndev, AMD_PEER_D0_EVENT);


		schedule_delayed_work(&ndev->hb_timer,
				      AMD_LINK_HB_TIMEOUT);
		break;
	default:
		dev_info(ndev_dev(ndev), "event status = 0x%x.\n", status);
		break;
	}
}
