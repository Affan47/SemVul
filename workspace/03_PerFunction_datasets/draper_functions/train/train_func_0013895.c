recalculate_sweep(Client *c, int x1, int y1, int x2, int y2, unsigned force) {
	if (force || c->oldw == 0) {
		c->oldw = 0;
		c->width = abs(x1 - x2);
		c->width -= (c->width - c->base_width) % c->width_inc;
		if (c->min_width && c->width < c->min_width)
			c->width = c->min_width;
		if (c->max_width && c->width > c->max_width)
			c->width = c->max_width;
		c->x = (x1 <= x2) ? x1 : x1 - c->width;
	}
	if (force || c->oldh == 0)  {
		c->oldh = 0;
		c->height = abs(y1 - y2);
		c->height -= (c->height - c->base_height) % c->height_inc;
		if (c->min_height && c->height < c->min_height)
			c->height = c->min_height;
		if (c->max_height && c->height > c->max_height)
			c->height = c->max_height;
		c->y = (y1 <= y2) ? y1 : y1 - c->height;
	}
}
