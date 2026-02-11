graph_map_color(state_t *s, int color, int priority, int control)
{
	gfx_color_t retval;

	if (s->resmgr->sci_version < SCI_VERSION_01_VGA)
	{
		retval = s->ega_colors[(color >=0 && color < 16)? color : 0];
		gfxop_set_color(s->gfx_state, &retval, (color < 0)? -1 : retval.visual.r, retval.visual.g, retval.visual.b,
				(color == -1)? 255 : 0, priority, control);
	} else
	{
		retval.visual = *(get_pic_color(s, color));
		retval.alpha = 0;
		retval.priority = priority;
		retval.control = control;
		retval.mask =
			GFX_MASK_VISUAL |
			((priority >= 0)? GFX_MASK_PRIORITY : 0) |
			((control >= 0)? GFX_MASK_CONTROL : 0);
	};

	return retval;
}
