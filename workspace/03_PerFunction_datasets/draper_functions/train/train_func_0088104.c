vesafb_destroy(struct fb_info *info)
{
	struct vesafb_par *par = info->par;

	fb_dealloc_cmap(&info->cmap);
	arch_phys_wc_del(par->wc_cookie);
	if (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(info->apertures->ranges[0].base, info->apertures->ranges[0].size);
}
