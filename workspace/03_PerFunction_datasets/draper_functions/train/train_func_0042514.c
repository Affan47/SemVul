move_waypoint(level *lvl, waypoint *w, int newx, int newy)
{
	if (!pos_inside_level(newx, newy, lvl))
		return;

	w->x = newx;
	w->y = newy;
}
