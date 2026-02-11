ipath_query_port(struct ib_device *ibdev,
			    u8 port, struct ib_port_attr *props)
{
	struct ipath_ibdev *dev = to_idev(ibdev);
	struct ipath_devdata *dd = dev->dd;
	enum ib_mtu mtu;
	u16 lid = dd->ipath_lid;
	u64 ibcstat;

	memset(props, 0, sizeof(*props));
	props->lid = lid ? lid : be16_to_cpu(IB_LID_PERMISSIVE);
	props->lmc = dd->ipath_lmc;
	props->sm_lid = dev->sm_lid;
	props->sm_sl = dev->sm_sl;
	ibcstat = dd->ipath_lastibcstat;

	props->state = ipath_ib_linkstate(dd, ibcstat) + 1;


	props->phys_state =
		ipath_cvt_physportstate[dd->ipath_lastibcstat &
		dd->ibcs_lts_mask];
	props->port_cap_flags = dev->port_cap_flags;
	props->gid_tbl_len = 1;
	props->max_msg_sz = 0x80000000;
	props->pkey_tbl_len = ipath_get_npkeys(dd);
	props->bad_pkey_cntr = ipath_get_cr_errpkey(dd) -
		dev->z_pkey_violations;
	props->qkey_viol_cntr = dev->qkey_violations;
	props->active_width = dd->ipath_link_width_active;

	props->active_speed = dd->ipath_link_speed_active;
	props->max_vl_num = 1;
	props->init_type_reply = 0;

	props->max_mtu = ipath_mtu4096 ? IB_MTU_4096 : IB_MTU_2048;
	switch (dd->ipath_ibmtu) {
	case 4096:
		mtu = IB_MTU_4096;
		break;
	case 2048:
		mtu = IB_MTU_2048;
		break;
	case 1024:
		mtu = IB_MTU_1024;
		break;
	case 512:
		mtu = IB_MTU_512;
		break;
	case 256:
		mtu = IB_MTU_256;
		break;
	default:
		mtu = IB_MTU_2048;
	}
	props->active_mtu = mtu;
	props->subnet_timeout = dev->subnet_timeout;

	return 0;
}
