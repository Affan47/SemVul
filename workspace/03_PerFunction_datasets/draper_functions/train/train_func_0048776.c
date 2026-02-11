set_nservers(struct net_device *dev, unsigned int val)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;

	if (adap->flags & FULL_INIT_DONE)
		return -EBUSY;
	if (val > t3_mc5_size(&adap->mc5) - adap->params.mc5.nfilters -
	    MC5_MIN_TIDS)
		return -EINVAL;
	adap->params.mc5.nservers = val;
	return 0;
}
