xy_to_button(WinManager *man, int x, int y)
{
	ManGeometry *g;
	int row, col, box, index;

	g = figure_geometry(man);
	row = y / g->boxheight;
	col = x / g->boxwidth;

	if (x >= 0 && x <= g->width &&
	    y >= 0 && y <= g->height && col < g->cols)
	{
		box = row * g->cols + col;
		index = box_to_index(man, box);
		if (index >= 0 && index < man->buttons.num_windows)
		{
			return man->buttons.buttons[index];
		}
	}

	return NULL;
}
