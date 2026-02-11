fb_find_best_mode(const struct fb_var_screeninfo *var,
					     struct list_head *head)
{
	struct list_head *pos;
	struct fb_modelist *modelist;
	struct fb_videomode *mode, *best = NULL;
	u32 diff = -1;

	list_for_each(pos, head) {
		u32 d;

		modelist = list_entry(pos, struct fb_modelist, list);
		mode = &modelist->mode;

		if (mode->xres >= var->xres && mode->yres >= var->yres) {
			d = (mode->xres - var->xres) +
				(mode->yres - var->yres);
			if (diff > d) {
				diff = d;
				best = mode;
			} else if (diff == d && best &&
				   mode->refresh > best->refresh)
				best = mode;
		}
	}
	return best;
}
