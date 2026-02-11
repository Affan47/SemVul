cairogen_ellipse(GVJ_t * job, pointf * A, int filled)
{
    obj_state_t *obj = job->obj;
    cairo_t *cr = (cairo_t *) job->context;
    cairo_matrix_t matrix;
    double rx, ry;

    cairogen_set_penstyle(job, cr);

    cairo_get_matrix(cr, &matrix);

    rx = A[1].x - A[0].x;
    ry = A[1].y - A[0].y;

#define RMIN 0.01
if (rx < RMIN) rx = RMIN;
if (ry < RMIN) ry = RMIN;

    cairo_translate(cr, A[0].x, -A[0].y);
    cairo_scale(cr, rx, ry);
    cairo_move_to(cr, 1., 0.);
    cairo_arc(cr, 0., 0., 1., 0., 2 * M_PI);

    cairo_set_matrix(cr, &matrix);

    if (filled == GRADIENT || filled == (RGRADIENT)) {
	cairo_gradient_fill (cr, obj, filled, A, 2);
    }
    else if (filled) {
	cairogen_set_color(cr, &(obj->fillcolor));
	cairo_fill_preserve(cr);
    }
    cairogen_set_color(cr, &(obj->pencolor));
    cairo_stroke(cr);
}
