fbcon_suspended(struct fb_info *info)
{
	struct vc_data *vc = NULL;
	struct fbcon_ops *ops = info->fbcon_par;

	if (!ops || ops->currcon < 0)
		return;
	vc = vc_cons[ops->currcon].d;


	fbcon_cursor(vc, CM_ERASE);
}
