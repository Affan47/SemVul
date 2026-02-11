usnic_ib_query_device(struct ib_device *ibdev,
			  struct ib_device_attr *props,
			  struct ib_udata *uhw)
{
	struct usnic_ib_dev *us_ibdev = to_usdev(ibdev);
	union ib_gid gid;
	struct ethtool_drvinfo info;
	struct ethtool_cmd cmd;
	int qp_per_vf;

	usnic_dbg("\n");
	if (uhw->inlen || uhw->outlen)
		return -EINVAL;

	mutex_lock(&us_ibdev->usdev_lock);
	us_ibdev->netdev->ethtool_ops->get_drvinfo(us_ibdev->netdev, &info);
	us_ibdev->netdev->ethtool_ops->get_settings(us_ibdev->netdev, &cmd);
	memset(props, 0, sizeof(*props));
	usnic_mac_ip_to_gid(us_ibdev->ufdev->mac, us_ibdev->ufdev->inaddr,
			&gid.raw[0]);
	memcpy(&props->sys_image_guid, &gid.global.interface_id,
		sizeof(gid.global.interface_id));
	usnic_ib_fw_string_to_u64(&info.fw_version[0], &props->fw_ver);
	props->max_mr_size = USNIC_UIOM_MAX_MR_SIZE;
	props->page_size_cap = USNIC_UIOM_PAGE_SIZE;
	props->vendor_id = PCI_VENDOR_ID_CISCO;
	props->vendor_part_id = PCI_DEVICE_ID_CISCO_VIC_USPACE_NIC;
	props->hw_ver = us_ibdev->pdev->subsystem_device;
	qp_per_vf = max(us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_WQ],
			us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_RQ]);
	props->max_qp = qp_per_vf *
		atomic_read(&us_ibdev->vf_cnt.refcount);
	props->device_cap_flags = IB_DEVICE_PORT_ACTIVE_EVENT |
		IB_DEVICE_SYS_IMAGE_GUID | IB_DEVICE_BLOCK_MULTICAST_LOOPBACK;
	props->max_cq = us_ibdev->vf_res_cnt[USNIC_VNIC_RES_TYPE_CQ] *
		atomic_read(&us_ibdev->vf_cnt.refcount);
	props->max_pd = USNIC_UIOM_MAX_PD_CNT;
	props->max_mr = USNIC_UIOM_MAX_MR_CNT;
	props->local_ca_ack_delay = 0;
	props->max_pkeys = 0;
	props->atomic_cap = IB_ATOMIC_NONE;
	props->masked_atomic_cap = props->atomic_cap;
	props->max_qp_rd_atom = 0;
	props->max_qp_init_rd_atom = 0;
	props->max_res_rd_atom = 0;
	props->max_srq = 0;
	props->max_srq_wr = 0;
	props->max_srq_sge = 0;
	props->max_fast_reg_page_list_len = 0;
	props->max_mcast_grp = 0;
	props->max_mcast_qp_attach = 0;
	props->max_total_mcast_qp_attach = 0;
	props->max_map_per_fmr = 0;


	mutex_unlock(&us_ibdev->usdev_lock);

	return 0;
}
