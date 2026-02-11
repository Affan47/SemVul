smc_netdev_set_ecmd(struct net_device *dev, struct ethtool_cmd *ecmd)
{
    u16 tmp;
    unsigned int ioaddr = dev->base_addr;

    if (ethtool_cmd_speed(ecmd) != SPEED_10)
	return -EINVAL;
    if (ecmd->duplex != DUPLEX_HALF && ecmd->duplex != DUPLEX_FULL)
    	return -EINVAL;
    if (ecmd->port != PORT_TP && ecmd->port != PORT_AUI)
	return -EINVAL;
    if (ecmd->transceiver != XCVR_INTERNAL)
    	return -EINVAL;

    if (ecmd->port == PORT_AUI)
	smc_set_xcvr(dev, 1);
    else
	smc_set_xcvr(dev, 0);

    SMC_SELECT_BANK(0);
    tmp = inw(ioaddr + TCR);
    if (ecmd->duplex == DUPLEX_FULL)
	tmp |= TCR_FDUPLX;
    else
	tmp &= ~TCR_FDUPLX;
    outw(tmp, ioaddr + TCR);

    return 0;
}
