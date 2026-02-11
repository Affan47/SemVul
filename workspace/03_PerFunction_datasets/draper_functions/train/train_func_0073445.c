do_stop(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    struct local_info *lp = netdev_priv(dev);
    struct pcmcia_device *link = lp->p_dev;

    dev_dbg(&link->dev, "do_stop(%p)\n", dev);

    if (!link)
	return -ENODEV;

    netif_stop_queue(dev);

    SelectPage(0);
    PutByte(XIRCREG_CR, 0);
    SelectPage(0x01);
    PutByte(XIRCREG1_IMR0, 0x00);
    SelectPage(4);
    PutByte(XIRCREG4_GPR1, 0);
    SelectPage(0);

    link->open--;
    return 0;
}
