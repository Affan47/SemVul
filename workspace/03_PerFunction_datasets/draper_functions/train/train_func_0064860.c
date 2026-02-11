fz_adjust_rect_for_stroke(fz_rect *r, fz_stroke_state *stroke, fz_matrix *ctm)
{
	float expand;

	if (!stroke)
		return;
	expand = stroke->linewidth;
	if (expand == 0)
		expand = 1.0f;
	expand *= fz_matrix_max_expansion(*ctm);
	if ((stroke->linejoin == FZ_LINEJOIN_MITER || stroke->linejoin == FZ_LINEJOIN_MITER_XPS) && stroke->miterlimit > 1)
		expand *= stroke->miterlimit;
	r->x0 -= expand;
	r->y0 -= expand;
	r->x1 += expand;
	r->y1 += expand;
}
