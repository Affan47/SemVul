erase_dirty_grid(struct atarimo_data *mo, const struct rectangle *cliprect)
{
	int sx = cliprect->min_x >> mo->tilexshift;
	int ex = cliprect->max_x >> mo->tilexshift;
	int sy = cliprect->min_y >> mo->tileyshift;
	int ey = cliprect->max_y >> mo->tileyshift;
	int y;


	for (y = sy; y <= ey; y++)
	{

		UINT8 *dirtybase = get_dirty_base(mo, cliprect->min_x, y << mo->tileyshift);
		memset(dirtybase, 0, ex - sx + 1);
	}
}
