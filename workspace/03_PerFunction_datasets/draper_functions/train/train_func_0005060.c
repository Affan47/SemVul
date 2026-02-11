ocrdma_query_port(struct ib_device *ibdev,
		      u8 port, struct ib_port_attr *props)
{
	enum ib_port_state port_state;
	struct ocrdma_dev *dev;
	struct net_device *netdev;

	dev = get_ocrdma_dev(ibdev);
	if (port > 1) {
		pr_err("%s(%d) invalid_port=0x%x\n", __func__,
		       dev->id, port);
		return -EINVAL;
	}
	netdev = dev->nic_info.netdev;
	if (netif_running(netdev) && netif_oper_up(netdev)) {
		port_state = IB_PORT_ACTIVE;
		props->phys_state = 5;
	} else {
		port_state = IB_PORT_DOWN;
		props->phys_state = 3;
	}
	props->max_mtu = IB_MTU_4096;
	props->active_mtu = iboe_get_mtu(netdev->mtu);
	props->lid = 0;
	props->lmc = 0;
	props->sm_lid = 0;
	props->sm_sl = 0;
	props->state = port_state;
	props->port_cap_flags =
	    IB_PORT_CM_SUP |
	    IB_PORT_REINIT_SUP |
	    IB_PORT_DEVICE_MGMT_SUP | IB_PORT_VENDOR_CLASS_SUP |
	    IB_PORT_IP_BASED_GIDS;
	props->gid_tbl_len = OCRDMA_MAX_SGID;
	props->pkey_tbl_len = 1;
	props->bad_pkey_cntr = 0;
	props->qkey_viol_cntr = 0;
	get_link_speed_and_width(dev, &props->active_speed,
				 &props->active_width);
	props->max_msg_sz = 0x80000000;
	props->max_vl_num = 4;
	return 0;
}
