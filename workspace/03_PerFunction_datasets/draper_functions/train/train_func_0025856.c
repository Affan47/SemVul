mhz_mfc_config(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct smc_private *smc = netdev_priv(dev);
    unsigned int offset;
    int i;

    link->config_flags |= CONF_ENABLE_SPKR | CONF_ENABLE_IRQ |
	    CONF_AUTO_SET_IO;


    if (pcmcia_loop_config(link, mhz_mfc_config_check, NULL))
	    return -ENODEV;

    dev->base_addr = link->resource[0]->start;


    link->resource[2]->flags = WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[2]->start = link->resource[2]->end = 0;
    i = pcmcia_request_window(link, link->resource[2], 0);
    if (i != 0)
	    return -ENODEV;

    smc->base = ioremap(link->resource[2]->start,
		    resource_size(link->resource[2]));
    offset = (smc->manfid == MANFID_MOTOROLA) ? link->config_base : 0;
    i = pcmcia_map_mem_page(link, link->resource[2], offset);
    if ((i == 0) &&
	(smc->manfid == MANFID_MEGAHERTZ) &&
	(smc->cardid == PRODID_MEGAHERTZ_EM3288))
	    mhz_3288_power(link);

    return 0;
}
