ray_update_multi_list(struct net_device *dev, int all)
{
	int ccsindex;
	struct ccs __iomem *pccs;
	ray_dev_t *local = netdev_priv(dev);
	struct pcmcia_device *link = local->finder;
	void __iomem *p = local->sram + HOST_TO_ECF_BASE;

	if (!(pcmcia_dev_present(link))) {
		dev_dbg(&link->dev, "ray_update_multi_list - device not present\n");
		return;
	} else
		dev_dbg(&link->dev, "ray_update_multi_list(%p)\n", dev);
	if ((ccsindex = get_free_ccs(local)) < 0) {
		dev_dbg(&link->dev, "ray_update_multi - No free ccs\n");
		return;
	}
	pccs = ccs_base(local) + ccsindex;
	writeb(CCS_UPDATE_MULTICAST_LIST, &pccs->cmd);

	if (all) {
		writeb(0xff, &pccs->var);
		local->num_multi = 0xff;
	} else {
		struct netdev_hw_addr *ha;
		int i = 0;


		netdev_for_each_mc_addr(ha, dev) {
			memcpy_toio(p, ha->addr, ETH_ALEN);
			dev_dbg(&link->dev, "ray_update_multi add addr %pm\n",
				ha->addr);
			p += ETH_ALEN;
			i++;
		}
		if (i > 256 / ADDRLEN)
			i = 256 / ADDRLEN;
		writeb((UCHAR) i, &pccs->var);
		dev_dbg(&link->dev, "ray_cs update_multi %d addresses in list\n", i);

		local->num_multi = i;
	}
	if (interrupt_ecf(local, ccsindex)) {
		dev_dbg(&link->dev,
		      "ray_cs update_multi failed - ECF not ready for intr\n");
		writeb(CCS_BUFFER_FREE, &(pccs++)->buffer_status);
	}
}
