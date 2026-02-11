fill_path_line_to (void *closure, GOPathPoint const *point)
{
	FillPathData *data = closure;

	if (data->first_point) {
		cairo_move_to (data->cairo, point->x, point->y);
		data->first_point = FALSE;
	}
	else
		cairo_line_to (data->cairo, point->x, point->y);
}
