tifm_ms_abort(unsigned long data)
{
	struct tifm_ms *host = (struct tifm_ms *)data;

	dev_dbg(&host->dev->dev, "status %x\n",
		readl(host->dev->addr + SOCK_MS_STATUS));
	printk(KERN_ERR
	       "%s : card failed to respond for a long period of time "
	       "(%x, %x)\n",
	       dev_name(&host->dev->dev), host->req ? host->req->tpc : 0,
	       host->cmd_flags);

	tifm_eject(host->dev);
}
