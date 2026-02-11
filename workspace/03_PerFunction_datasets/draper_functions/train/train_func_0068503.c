frame_get_sidebar_geometry(
	FvwmWindow *fw, DecorFaceStyle *borderstyle, rectangle *frame_g,
	rectangle *ret_g, Bool *ret_has_x_marks, Bool *ret_has_y_marks)
{
	int min_w;
	size_borders b;

	ret_g->x = 0;
	ret_g->y = 0;
	ret_g->width = 0;
	ret_g->height = 0;
	*ret_has_x_marks = False;
	*ret_has_y_marks = False;
	if (HAS_NO_BORDER(fw))
	{
		return;
	}

	if (!HAS_HANDLES(fw))
	{
		*ret_has_x_marks = False;
		*ret_has_y_marks = False;
	}
	else if (borderstyle == NULL)
	{
		if (fw->decor_state.parts_drawn & PART_X_HANDLES)
		{
			*ret_has_x_marks = True;
		}
		if (fw->decor_state.parts_drawn & PART_Y_HANDLES)
		{
			*ret_has_y_marks = True;
		}
	}
	else if (!DFS_HAS_HIDDEN_HANDLES(*borderstyle))
	{
		*ret_has_x_marks = True;
		*ret_has_y_marks = True;
	}
	ret_g->x = fw->corner_width;
	ret_g->y = fw->corner_width;
	min_w = 2 * fw->corner_width + 4;

	if (frame_g->width < min_w)
	{
		ret_g->x = frame_g->width / 3;
		*ret_has_y_marks = False;
	}
	if (frame_g->height < min_w)
	{
		ret_g->y = frame_g->height / 3;
		*ret_has_x_marks = False;
	}
	get_window_borders_no_title(fw, &b);
	if (ret_g->x < b.top_left.width)
	{
		ret_g->x = b.top_left.width;
	}
	if (ret_g->y < b.top_left.height)
	{
		ret_g->y = b.top_left.height;
	}

	ret_g->width = frame_g->width - 2 * ret_g->x;
	ret_g->height = frame_g->height - 2 * ret_g->y;

	return;
}
