make_valid_vtriangle(const Triangulation *triangulation,
                     Triangle *vtriangle,
                     guint hint)
{
    const Point *a = get_vpoint(triangulation, hint);
    const Point *b, *c;
    const guint *neighbours;
    gdouble phib, phic;
    guint i, len;

    vtriangle->ia = i = hint;
    neighbours = triangulation->voronoi + triangulation->vindex[i];
    len = triangulation->vindex[i+1] - triangulation->vindex[i];
    for (i = 0; i < len; i++) {
        vtriangle->ib = neighbours[i];
        vtriangle->ic = next_neighbour(neighbours, len, i);

        b = get_vpoint(triangulation, vtriangle->ib);
        phib = atan2(b->y - a->y, b->x - a->x);
        c = get_vpoint(triangulation, vtriangle->ic);
        phic = atan2(c->y - a->y, c->x - a->x);

        if (ccw_angle_convex(phib, phic)) {
            make_vtriangle(vtriangle, triangulation);
            return;
        }
    }

    g_assert_not_reached();
}
