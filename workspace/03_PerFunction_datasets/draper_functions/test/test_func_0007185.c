ywrap_down(struct vc_data *vc, int count)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_ops *ops = info->fbcon_par;
	struct display *p = &fb_display[vc->vc_num];

	p->yscroll -= count;
	if (p->yscroll < 0)
		p->yscroll += p->vrows;
	ops->var.xoffset = 0;
	ops->var.yoffset = p->yscroll * vc->vc_font.height;
	ops->var.vmode |= FB_VMODE_YWRAP;
	ops->update_start(info);
	scrollback_max -= count;
	if (scrollback_max < 0)
		scrollback_max = 0;
	scrollback_current = 0;
}
