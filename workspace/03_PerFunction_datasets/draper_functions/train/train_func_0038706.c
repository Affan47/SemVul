make_adjustment_matrix(const gs_point * request, const gs_rect * medium,
                       gs_matrix * pmat, bool scale, int rotate)
{
    double rx = request->x, ry = request->y;
    double mx = medium->q.x, my = medium->q.y;


    if (rotate & 1) {
        double temp = rx;

        rx = ry, ry = temp;
    }


    if (medium->p.x < mx) {
        if (rx < medium->p.x)
            mx = medium->p.x;
        else if (rx < mx)
            mx = rx;

    }
    if (medium->p.y < my) {
        if (ry < medium->p.y)
            my = medium->p.y;
        else if (ry < my)
            my = ry;

    }


    gs_make_translation(mx / 2, my / 2, pmat);


    if (rotate)
        gs_matrix_rotate(pmat, 90.0 * rotate, pmat);


    if (scale) {
        double xfactor = mx / rx;
        double yfactor = my / ry;
        double factor = min(xfactor, yfactor);

        gs_matrix_scale(pmat, factor, factor, pmat);
    }


    gs_matrix_translate(pmat, -request->x / 2, -request->y / 2, pmat);
}
