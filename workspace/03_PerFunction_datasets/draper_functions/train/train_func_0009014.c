dlfb_realloc_framebuffer(struct dlfb_data *dev, struct fb_info *info)
{
	int retval = -ENOMEM;
	int old_len = info->fix.smem_len;
	int new_len;
	unsigned char *old_fb = info->screen_base;
	unsigned char *new_fb;
	unsigned char *new_back = NULL;

	pr_warn("Reallocating framebuffer. Addresses will change!\n");

	new_len = info->fix.line_length * info->var.yres;

	if (PAGE_ALIGN(new_len) > old_len) {


		new_fb = vmalloc(new_len);
		if (!new_fb) {
			pr_err("Virtual framebuffer alloc failed\n");
			goto error;
		}

		if (info->screen_base) {
			memcpy(new_fb, old_fb, old_len);
			vfree(info->screen_base);
		}

		info->screen_base = new_fb;
		info->fix.smem_len = PAGE_ALIGN(new_len);
		info->fix.smem_start = (unsigned long) new_fb;
		info->flags = udlfb_info_flags;


		if (shadow)
			new_back = vzalloc(new_len);
		if (!new_back)
			pr_info("No shadow/backing buffer allocated\n");
		else {
			vfree(dev->backing_buffer);
			dev->backing_buffer = new_back;
		}
	}

	retval = 0;

error:
	return retval;
}
