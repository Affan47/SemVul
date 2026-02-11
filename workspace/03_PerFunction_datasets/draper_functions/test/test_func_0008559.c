fbcon_fb_blanked(struct fb_info *info, int blank)
{
	struct fbcon_ops *ops = info->fbcon_par;
	struct vc_data *vc;

	if (!ops || ops->currcon < 0)
		return;

	vc = vc_cons[ops->currcon].d;
	if (vc->vc_mode != KD_TEXT ||
			registered_fb[con2fb_map[ops->currcon]] != info)
		return;

	if (CON_IS_VISIBLE(vc)) {
		if (blank)
			do_blank_screen(0);
		else
			do_unblank_screen(0);
	}
	ops->blank_state = blank;
}
