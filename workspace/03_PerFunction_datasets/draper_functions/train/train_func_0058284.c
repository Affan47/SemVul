broadsheetfb_remove(struct platform_device *dev)
{
	struct fb_info *info = platform_get_drvdata(dev);

	if (info) {
		struct broadsheetfb_par *par = info->par;

		device_remove_file(info->dev, &dev_attr_loadstore_waveform);
		unregister_framebuffer(info);
		fb_deferred_io_cleanup(info);
		par->board->cleanup(par);
		fb_dealloc_cmap(&info->cmap);
		vfree((void *)info->screen_base);
		module_put(par->board->owner);
		framebuffer_release(info);
	}
	return 0;
}
