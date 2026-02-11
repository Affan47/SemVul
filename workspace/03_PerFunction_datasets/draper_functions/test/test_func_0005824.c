shape_clip0(inside_t * inside_context, node_t * n, pointf curve[4],
	    boolean left_inside)
{
    int i;
    double save_real_size;
    pointf c[4];

    save_real_size = ND_rw(n);
    for (i = 0; i < 4; i++) {
	c[i].x = curve[i].x - ND_coord(n).x;
	c[i].y = curve[i].y - ND_coord(n).y;
    }

    bezier_clip(inside_context, ND_shape(n)->fns->insidefn, c,
		left_inside);

    for (i = 0; i < 4; i++) {
	curve[i].x = c[i].x + ND_coord(n).x;
	curve[i].y = c[i].y + ND_coord(n).y;
    }
    ND_rw(n) = save_real_size;
}
