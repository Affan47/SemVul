e100_get_defaults(struct nic *nic)
{
	struct param_range rfds = { .min = 16, .max = 256, .count = 256 };
	struct param_range cbs  = { .min = 64, .max = 256, .count = 128 };


	nic->mac = (nic->flags & ich) ? mac_82559_D101M : nic->pdev->revision;
	if (nic->mac == mac_unknown)
		nic->mac = mac_82557_D100_A;

	nic->params.rfds = rfds;
	nic->params.cbs = cbs;


	nic->tx_threshold = 0xE0;


	nic->tx_command = cpu_to_le16(cb_tx | cb_tx_sf |
		((nic->mac >= mac_82558_D101_A4) ? cb_cid : cb_i));


	nic->blank_rfd.command = 0;
	nic->blank_rfd.rbd = cpu_to_le32(0xFFFFFFFF);
	nic->blank_rfd.size = cpu_to_le16(VLAN_ETH_FRAME_LEN + ETH_FCS_LEN);


	nic->mii.phy_id_mask = 0x1F;
	nic->mii.reg_num_mask = 0x1F;
	nic->mii.dev = nic->netdev;
	nic->mii.mdio_read = mdio_read;
	nic->mii.mdio_write = mdio_write;
}
