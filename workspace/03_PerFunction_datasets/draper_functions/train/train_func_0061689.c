cairogen_polygon(GVJ_t * job, pointf * A, int n, int filled)
{
    obj_state_t *obj = job->obj;
    cairo_t *cr = (cairo_t *) job->context;
    int i;

    cairogen_set_penstyle(job, cr);

    cairo_move_to(cr, A[0].x, -A[0].y);
    for (i = 1; i < n; i++)
    cairo_line_to(cr, A[i].x, -A[i].y);
    cairo_close_path(cr);
    if (filled == GRADIENT || filled == (RGRADIENT)) {
	cairo_gradient_fill (cr, obj, filled, A, n);
    }
    else if (filled) {
	cairogen_set_color(cr, &(obj->fillcolor));
	cairo_fill_preserve(cr);
    }
    cairogen_set_color(cr, &(obj->pencolor));
    cairo_stroke(cr);
}
