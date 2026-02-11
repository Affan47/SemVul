cxgb4_getcap(struct net_device *dev, int cap_id, u8 *caps)
{
	struct port_info *pi = netdev2pinfo(dev);

	switch (cap_id) {
	case DCB_CAP_ATTR_PG:
	case DCB_CAP_ATTR_PFC:
		*caps = true;
		break;

	case DCB_CAP_ATTR_PG_TCS:

		*caps = 0x80;
		break;

	case DCB_CAP_ATTR_PFC_TCS:

		*caps = 0x80;
		break;

	case DCB_CAP_ATTR_GSP:
		*caps = true;
		break;

	case DCB_CAP_ATTR_UP2TC:
	case DCB_CAP_ATTR_BCN:
		*caps = false;
		break;

	case DCB_CAP_ATTR_DCBX:
		*caps = pi->dcb.supported;
		break;

	default:
		*caps = false;
	}

	return 0;
}
