nemo_selection_canvas_item_point (EelCanvasItem *item,
				      double x,
				      double y,
				      int cx,
				      int cy,
				      EelCanvasItem **actual_item)
{
	NemoSelectionCanvasItem *self;
	double x1, y1, x2, y2;
	double hwidth;
	double dx, dy;
	double tmp;

	self = NEMO_SELECTION_CANVAS_ITEM (item);
	*actual_item = item;


	x1 = self->priv->x1;
	y1 = self->priv->y1;
	x2 = self->priv->x2;
	y2 = self->priv->y2;

	if (self->priv->outline_set) {
		hwidth = (self->priv->width / item->canvas->pixels_per_unit) / 2.0;

		x1 -= hwidth;
		y1 -= hwidth;
		x2 += hwidth;
		y2 += hwidth;
	} else
		hwidth = 0.0;


	if ((x >= x1) && (y >= y1) && (x <= x2) && (y <= y2)) {
		if (self->priv->fill_set || !self->priv->outline_set)
			return 0.0;

		dx = x - x1;
		tmp = x2 - x;
		if (tmp < dx)
			dx = tmp;

		dy = y - y1;
		tmp = y2 - y;
		if (tmp < dy)
			dy = tmp;

		if (dy < dx)
			dx = dy;

		dx -= 2.0 * hwidth;

		if (dx < 0.0)
			return 0.0;
		else
			return dx;
	}


	if (x < x1)
		dx = x1 - x;
	else if (x > x2)
		dx = x - x2;
	else
		dx = 0.0;

	if (y < y1)
		dy = y1 - y;
	else if (y > y2)
		dy = y - y2;
	else
		dy = 0.0;

	return sqrt (dx * dx + dy * dy);
}
