of_get_fb_videomode(struct device_node *np, struct fb_videomode *fb,
			int index)
{
	struct videomode vm;
	int ret;

	ret = of_get_videomode(np, &vm, index);
	if (ret)
		return ret;

	ret = fb_videomode_from_videomode(&vm, fb);
	if (ret)
		return ret;

	pr_debug("%s: got %dx%d display mode from %s\n",
		of_node_full_name(np), vm.hactive, vm.vactive, np->name);
	dump_fb_videomode(fb);

	return 0;
}
