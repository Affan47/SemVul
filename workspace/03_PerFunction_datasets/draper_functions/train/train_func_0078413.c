av7110_ipack_init(struct ipack *p, int size,
		      void (*func)(u8 *buf, int size, void *priv))
{
	if (!(p->buf = vmalloc(size*sizeof(u8)))) {
		printk(KERN_WARNING "Couldn't allocate memory for ipack\n");
		return -ENOMEM;
	}
	p->size = size;
	p->func = func;
	p->repack_subids = 0;
	av7110_ipack_reset(p);
	return 0;
}
