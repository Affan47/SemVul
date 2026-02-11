broadsheetfb_dpy_deferred_io(struct fb_info *info,
				struct list_head *pagelist)
{
	u16 y1 = 0, h = 0;
	int prev_index = -1;
	struct page *cur;
	struct fb_deferred_io *fbdefio = info->fbdefio;
	int h_inc;
	u16 yres = info->var.yres;
	u16 xres = info->var.xres;


	h_inc = DIV_ROUND_UP(PAGE_SIZE , xres);


	list_for_each_entry(cur, &fbdefio->pagelist, lru) {
		if (prev_index < 0) {

			y1 = (cur->index << PAGE_SHIFT) / xres;
			h = h_inc;
		} else if ((prev_index + 1) == cur->index) {

			h += h_inc;
		} else {

			broadsheetfb_dpy_update_pages(info->par, y1, y1 + h);

			y1 = (cur->index << PAGE_SHIFT) / xres;
			h = h_inc;
		}
		prev_index = cur->index;
	}


	if (h >= yres) {

		broadsheetfb_dpy_update(info->par);
	} else {
		broadsheetfb_dpy_update_pages(info->par, y1,
						min((u16) (y1 + h), yres));
	}
}
