region_erase(const region *loc)
{
	int i = 0;
	int w = loc->width;
	int h = loc->page_rows;

	if (loc->width <= 0 || loc->page_rows <= 0)
	{
		Term_get_size(&w, &h);
		if (loc->width <= 0) w -= loc->width;
		if (loc->page_rows <= 0) h -= loc->page_rows;
	}

	for (i = 0; i < h; i++)
		Term_erase(loc->col, loc->row + i, w);
}
