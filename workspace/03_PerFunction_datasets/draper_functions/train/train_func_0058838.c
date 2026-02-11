ipath_ht_get_ib_cfg(struct ipath_devdata *dd, int which)
{
	int ret;

	switch (which) {
	case IPATH_IB_CFG_LWID:
		ret = dd->ipath_link_width_active;
		break;
	case IPATH_IB_CFG_SPD:
		ret = dd->ipath_link_speed_active;
		break;
	case IPATH_IB_CFG_LWID_ENB:
		ret = dd->ipath_link_width_enabled;
		break;
	case IPATH_IB_CFG_SPD_ENB:
		ret = dd->ipath_link_speed_enabled;
		break;
	default:
		ret =  -ENOTSUPP;
		break;
	}
	return ret;
}
