maximize_disc_radius(InscribedDisc *disc, Edge *edges, guint n)
{
    gdouble x = disc->x, y = disc->y, r2best = HUGE_VAL;

    while (n--) {
        gdouble rax = edges->xa - x, ray = edges->ya - y,
                rbx = edges->xb - x, rby = edges->yb - y,
                deltax = edges->xb - edges->xa, deltay = edges->yb - edges->ya;
        gdouble ca = -(deltax*rax + deltay*ray),
                cb = deltax*rbx + deltay*rby;

        if (ca <= 0.0)
            edges->r2 = rax*rax + ray*ray;
        else if (cb <= 0.0)
            edges->r2 = rbx*rbx + rby*rby;
        else {
            gdouble tx = cb*rax + ca*rbx, ty = cb*ray + ca*rby, D = ca + cb;
            edges->r2 = (tx*tx + ty*ty)/(D*D);
        }

        if (edges->r2 < r2best)
            r2best = edges->r2;
        edges++;
    }

    return r2best;
}
