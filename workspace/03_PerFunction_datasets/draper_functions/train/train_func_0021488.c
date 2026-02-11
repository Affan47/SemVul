curs_copy(cursor_info_t *dest, cursor_info_t *src) {
	if (src->data != NULL) {
		dest->data = strdup(src->data);
	} else {
		dest->data = NULL;
	}
	if (src->mask != NULL) {
		dest->mask = strdup(src->mask);
	} else {
		dest->mask = NULL;
	}
	dest->wx = src->wx;
	dest->wy = src->wy;
	dest->sx = src->sx;
	dest->sy = src->sy;
	dest->reverse = src->reverse;
	dest->rfb = src->rfb;

	if (rotating && rotating_cursors && dest->data != NULL) {
		int tx, ty;
		rotate_curs(dest->data, src->data, src->wx, src->wy, 1);
		rotate_curs(dest->mask, src->mask, src->wx, src->wy, 1);
		rotate_coords(dest->sx, dest->sy, &tx, &ty, src->wx, src->wy);
		dest->sx = tx;
		dest->sy = ty;
		if (! rotating_same) {
			dest->wx = src->wy;
			dest->wy = src->wx;
		}
	}
}
