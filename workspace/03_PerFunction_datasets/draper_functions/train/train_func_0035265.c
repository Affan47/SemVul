renderer_update_sizes(void *renderer)
{
	RendererTiles *rt = (RendererTiles *)renderer;

	rt->stereo_off_x = 0;
	rt->stereo_off_y = 0;

	if (rt->stereo_mode & PR_STEREO_RIGHT)
		{
		if (rt->stereo_mode & PR_STEREO_HORIZ)
			{
			rt->stereo_off_x = rt->pr->viewport_width;
			}
		else if (rt->stereo_mode & PR_STEREO_VERT)
			{
			rt->stereo_off_y = rt->pr->viewport_height;
			}
		else if (rt->stereo_mode & PR_STEREO_FIXED)
			{
			rt->stereo_off_x = rt->pr->stereo_fixed_x_right;
			rt->stereo_off_y = rt->pr->stereo_fixed_y_right;
			}
		}
	else
		{
		if (rt->stereo_mode & PR_STEREO_FIXED)
			{
			rt->stereo_off_x = rt->pr->stereo_fixed_x_left;
			rt->stereo_off_y = rt->pr->stereo_fixed_y_left;
			}
		}
        DEBUG_1("update size: %p  %d %d   %d %d", rt, rt->stereo_off_x, rt->stereo_off_y, rt->pr->viewport_width, rt->pr->viewport_height);
	rt_sync_scroll(rt);
	rt_overlay_update_sizes(rt);
}
