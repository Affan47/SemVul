get_hwinfo(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    u_char __iomem *base, *virt;
    int i, j;


    link->resource[2]->flags |= WIN_DATA_WIDTH_8|WIN_MEMORY_TYPE_AM|WIN_ENABLE;
    link->resource[2]->start = 0; link->resource[2]->end = 0;
    i = pcmcia_request_window(link, link->resource[2], 0);
    if (i != 0)
	return NULL;

    virt = ioremap(link->resource[2]->start,
	    resource_size(link->resource[2]));
    for (i = 0; i < NR_INFO; i++) {
	pcmcia_map_mem_page(link, link->resource[2],
		hw_info[i].offset & ~(resource_size(link->resource[2])-1));
	base = &virt[hw_info[i].offset & (resource_size(link->resource[2])-1)];
	if ((readb(base+0) == hw_info[i].a0) &&
	    (readb(base+2) == hw_info[i].a1) &&
	    (readb(base+4) == hw_info[i].a2)) {
		for (j = 0; j < 6; j++)
		    dev->dev_addr[j] = readb(base + (j<<1));
		break;
	}
    }

    iounmap(virt);
    j = pcmcia_release_window(link, link->resource[2]);
    return (i < NR_INFO) ? hw_info+i : NULL;
}
