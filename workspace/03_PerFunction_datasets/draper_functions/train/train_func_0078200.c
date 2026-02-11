get_custom_topedge (int *x, int *y)
{
	if (isnativevidbuf ()) {
		*x = visible_left_border + (DISPLAY_LEFT_SHIFT << currprefs.gfx_resolution);
		*y = minfirstline << currprefs.gfx_vresolution;
	} else {
		*x = 0;
		*y = 0;
	}
}
