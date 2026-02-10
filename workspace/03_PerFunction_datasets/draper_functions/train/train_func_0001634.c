arcfb_probe(struct platform_device *dev)
{
	struct fb_info *info;
	int retval = -ENOMEM;
	int videomemorysize;
	unsigned char *videomemory;
	struct arcfb_par *par;
	int i;

	videomemorysize = (((64*64)*num_cols)*num_rows)/8;


	videomemory = vzalloc(videomemorysize);
	if (!videomemory)
		return retval;

	info = framebuffer_alloc(sizeof(struct arcfb_par), &dev->dev);
	if (!info)
		goto err;

	info->screen_base = (char __iomem *)videomemory;
	info->fbops = &arcfb_ops;

	info->var = arcfb_var;
	info->fix = arcfb_fix;
	par = info->par;
	par->info = info;

	if (!dio_addr || !cio_addr || !c2io_addr) {
		printk(KERN_WARNING "no IO addresses supplied\n");
		goto err1;
	}
	par->dio_addr = dio_addr;
	par->cio_addr = cio_addr;
	par->c2io_addr = c2io_addr;
	par->cslut[0] = 0x00;
	par->cslut[1] = 0x06;
	info->flags = FBINFO_FLAG_DEFAULT;
	spin_lock_init(&par->lock);
	retval = register_framebuffer(info);
	if (retval < 0)
		goto err1;
	platform_set_drvdata(dev, info);
	if (irq) {
		par->irq = irq;
		if (request_irq(par->irq, &arcfb_interrupt, IRQF_SHARED,
				"arcfb", info)) {
			printk(KERN_INFO
				"arcfb: Failed req IRQ %d\n", par->irq);
			retval = -EBUSY;
			goto err1;
		}
	}
	fb_info(info, "Arc frame buffer device, using %dK of video memory\n",
		videomemorysize >> 10);


	for (i = 0; i < num_cols * num_rows; i++) {
		ks108_writeb_ctl(par, i, KS_DPY_OFF);
		ks108_set_start_line(par, i, 0);
		ks108_set_yaddr(par, i, 0);
		ks108_set_xaddr(par, i, 0);
		ks108_writeb_ctl(par, i, KS_DPY_ON);
	}


	if (!nosplash) {
		for (i = 0; i < num_cols * num_rows; i++) {
			fb_info(info, "splashing lcd %d\n", i);
			ks108_set_start_line(par, i, 0);
			ks108_clear_lcd(par, i);
		}
	}

	return 0;
err1:
	framebuffer_release(info);
err:
	vfree(videomemory);
	return retval;
}
