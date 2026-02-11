srom_infoleaf_info(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    int i, count;
    u_char *p;


    for (i=0; i<INFOLEAF_SIZE; i++) {
	if (lp->chipset == infoleaf_array[i].chipset) break;
    }
    if (i == INFOLEAF_SIZE) {
	lp->useSROM = false;
	printk("%s: Cannot find correct chipset for SROM decoding!\n",
	                                                          dev->name);
	return -ENXIO;
    }

    lp->infoleaf_fn = infoleaf_array[i].fn;


    count = *((u_char *)&lp->srom + 19);
    p  = (u_char *)&lp->srom + 26;

    if (count > 1) {
	for (i=count; i; --i, p+=3) {
	    if (lp->device == *p) break;
	}
	if (i == 0) {
	    lp->useSROM = false;
	    printk("%s: Cannot find correct PCI device [%d] for SROM decoding!\n",
	                                               dev->name, lp->device);
	    return -ENXIO;
	}
    }

	lp->infoleaf_offset = get_unaligned_le16(p + 1);

    return 0;
}
