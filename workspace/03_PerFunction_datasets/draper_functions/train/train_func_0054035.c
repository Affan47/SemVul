get_box(unit_type x, unit_type y, unit_type *xa, unit_type *ya)
{
	struct box **box, **best = NULL;
	struct box *b;
	double size, best_size;

	for (box = &boxes; *box; box = &(*box)->next) {
		if ((*box)->x < x || (*box)->y < y)
			continue;
		size = (double) (*box)->x*(*box)->y;
		if (!best || size < best_size) {
			best = box;
			best_size = size;
		}
	}
	if (!best)
		return 0;
	b = *best;
	if (xa)
		*xa = b->x0;
	if (ya)
		*ya = b->y0+b->y-y;

	*best = b->next;
	add_box(b->x0+x, b->y0, b->x0+b->x, b->y0+b->y);
	add_box(b->x0, b->y0, b->x0+x, b->y0+b->y-y);
	free(b);

	return 1;
}
