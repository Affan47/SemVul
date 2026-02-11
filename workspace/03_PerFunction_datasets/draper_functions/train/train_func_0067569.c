saa7164_buffer_cfg_port(struct saa7164_port *port)
{
	struct tmHWStreamParameters *params = &port->hw_streamingparams;
	struct saa7164_dev *dev = port->dev;
	struct saa7164_buffer *buf;
	struct list_head *c, *n;
	int i = 0;

	dprintk(DBGLVL_BUF, "%s(port=%d)\n", __func__, port->nr);

	saa7164_writel(port->bufcounter, 0);
	saa7164_writel(port->pitch, params->pitch);
	saa7164_writel(port->bufsize, params->pitch * params->numberoflines);

	dprintk(DBGLVL_BUF, " configured:\n");
	dprintk(DBGLVL_BUF, "   lmmio       0x%p\n", dev->lmmio);
	dprintk(DBGLVL_BUF, "   bufcounter  0x%x = 0x%x\n", port->bufcounter,
		saa7164_readl(port->bufcounter));

	dprintk(DBGLVL_BUF, "   pitch       0x%x = %d\n", port->pitch,
		saa7164_readl(port->pitch));

	dprintk(DBGLVL_BUF, "   bufsize     0x%x = %d\n", port->bufsize,
		saa7164_readl(port->bufsize));

	dprintk(DBGLVL_BUF, "   buffercount = %d\n", port->hwcfg.buffercount);
	dprintk(DBGLVL_BUF, "   bufoffset = 0x%x\n", port->bufoffset);
	dprintk(DBGLVL_BUF, "   bufptr32h = 0x%x\n", port->bufptr32h);
	dprintk(DBGLVL_BUF, "   bufptr32l = 0x%x\n", port->bufptr32l);


	mutex_lock(&port->dmaqueue_lock);
	list_for_each_safe(c, n, &port->dmaqueue.list) {
		buf = list_entry(c, struct saa7164_buffer, list);

		if (buf->flags != SAA7164_BUFFER_FREE)
			BUG();


		saa7164_buffer_activate(buf, i);


		if (i++ > port->hwcfg.buffercount)
			BUG();

	}
	mutex_unlock(&port->dmaqueue_lock);

	return 0;
}
