fbcon_rotate(struct fb_info *info, u32 rotate)
{
	struct fbcon_ops *ops= info->fbcon_par;
	struct fb_info *fb_info;

	if (!ops || ops->currcon == -1)
		return;

	fb_info = registered_fb[con2fb_map[ops->currcon]];

	if (info == fb_info) {
		struct display *p = &fb_display[ops->currcon];

		if (rotate < 4)
			p->con_rotate = rotate;
		else
			p->con_rotate = 0;

		fbcon_modechanged(info);
	}
}
