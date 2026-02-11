bnxt_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	switch (cmd) {
	case SIOCGMIIPHY:

	case SIOCGMIIREG: {
		if (!netif_running(dev))
			return -EAGAIN;

		return 0;
	}

	case SIOCSMIIREG:
		if (!netif_running(dev))
			return -EAGAIN;

		return 0;

	default:

		break;
	}
	return -EOPNOTSUPP;
}
