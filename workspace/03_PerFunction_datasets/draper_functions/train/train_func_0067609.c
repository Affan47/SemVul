lxfb_map_video_memory(struct fb_info *info, struct pci_dev *dev)
{
	struct lxfb_par *par = info->par;
	int ret;

	ret = pci_enable_device(dev);

	if (ret)
		return ret;

	ret = pci_request_region(dev, 0, "lxfb-framebuffer");

	if (ret)
		return ret;

	ret = pci_request_region(dev, 1, "lxfb-gp");

	if (ret)
		return ret;

	ret = pci_request_region(dev, 2, "lxfb-vg");

	if (ret)
		return ret;

	ret = pci_request_region(dev, 3, "lxfb-vp");

	if (ret)
		return ret;

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = vram ? vram : lx_framebuffer_size();

	info->screen_base = ioremap(info->fix.smem_start, info->fix.smem_len);

	ret = -ENOMEM;

	if (info->screen_base == NULL)
		return ret;

	par->gp_regs = pci_ioremap_bar(dev, 1);

	if (par->gp_regs == NULL)
		return ret;

	par->dc_regs = pci_ioremap_bar(dev, 2);

	if (par->dc_regs == NULL)
		return ret;

	par->vp_regs = pci_ioremap_bar(dev, 3);

	if (par->vp_regs == NULL)
		return ret;

	write_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
	write_dc(par, DC_GLIU0_MEM_OFFSET, info->fix.smem_start & 0xFF000000);
	write_dc(par, DC_UNLOCK, DC_UNLOCK_LOCK);

	dev_info(&dev->dev, "%d KB of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	return 0;
}
