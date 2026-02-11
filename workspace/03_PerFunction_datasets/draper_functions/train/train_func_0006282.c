util_clip_triangle(gint x1, gint y1, gint x2, gint y2, gint x3, gint y3,
			gint *rx, gint *ry, gint *rw, gint *rh)
{
	gint tx, ty, tw, th;

	tx = MIN(x1, x2);
	tx = MIN(tx, x3);
	ty = MIN(y1, y2);
	ty = MIN(ty, y3);
	tw = MAX(abs(x1 - x2), abs(x2 - x3));
	tw = MAX(tw, abs(x3 - x1));
	th = MAX(abs(y1 - y2), abs(y2 - y3));
	th = MAX(th, abs(y3 - y1));

	*rx = tx;
	*ry = ty;
	*rw = tw;
	*rh = th;
}
