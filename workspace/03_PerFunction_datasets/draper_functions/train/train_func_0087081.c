octeon_core_drv_init(struct octeon_recv_info *recv_info, void *buf)
{
	u32 i;
	char app_name[16];
	struct octeon_device *oct = (struct octeon_device *)buf;
	struct octeon_recv_pkt *recv_pkt = recv_info->recv_pkt;
	struct octeon_core_setup *cs = NULL;
	u32 num_nic_ports = 0;

	if (OCTEON_CN6XXX(oct))
		num_nic_ports =
			CFG_GET_NUM_NIC_PORTS(CHIP_FIELD(oct, cn6xxx, conf));

	if (atomic_read(&oct->status) >= OCT_DEV_RUNNING) {
		dev_err(&oct->pci_dev->dev, "Received CORE OK when device state is 0x%x\n",
			atomic_read(&oct->status));
		goto core_drv_init_err;
	}

	strncpy(app_name,
		get_oct_app_string(
		(u32)recv_pkt->rh.r_core_drv_init.app_mode),
		sizeof(app_name) - 1);
	oct->app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;
	if (recv_pkt->rh.r_core_drv_init.app_mode == CVM_DRV_NIC_APP) {
		oct->fw_info.max_nic_ports =
			(u32)recv_pkt->rh.r_core_drv_init.max_nic_ports;
		oct->fw_info.num_gmx_ports =
			(u32)recv_pkt->rh.r_core_drv_init.num_gmx_ports;
	}

	if (oct->fw_info.max_nic_ports < num_nic_ports) {
		dev_err(&oct->pci_dev->dev,
			"Config has more ports than firmware allows (%d > %d).\n",
			num_nic_ports, oct->fw_info.max_nic_ports);
		goto core_drv_init_err;
	}
	oct->fw_info.app_cap_flags = recv_pkt->rh.r_core_drv_init.app_cap_flags;
	oct->fw_info.app_mode = (u32)recv_pkt->rh.r_core_drv_init.app_mode;

	atomic_set(&oct->status, OCT_DEV_CORE_OK);

	cs = &core_setup[oct->octeon_id];

	if (recv_pkt->buffer_size[0] != sizeof(*cs)) {
		dev_dbg(&oct->pci_dev->dev, "Core setup bytes expected %u found %d\n",
			(u32)sizeof(*cs),
			recv_pkt->buffer_size[0]);
	}

	memcpy(cs, get_rbd(recv_pkt->buffer_ptr[0]), sizeof(*cs));
	strncpy(oct->boardinfo.name, cs->boardname, OCT_BOARD_NAME);
	strncpy(oct->boardinfo.serial_number, cs->board_serial_number,
		OCT_SERIAL_LEN);

	octeon_swap_8B_data((u64 *)cs, (sizeof(*cs) >> 3));

	oct->boardinfo.major = cs->board_rev_major;
	oct->boardinfo.minor = cs->board_rev_minor;

	dev_info(&oct->pci_dev->dev,
		 "Running %s (%llu Hz)\n",
		 app_name, CVM_CAST64(cs->corefreq));

core_drv_init_err:
	for (i = 0; i < recv_pkt->buffer_count; i++)
		recv_buffer_free(recv_pkt->buffer_ptr[i]);
	octeon_free_recv_info(recv_info);
	return 0;
}
