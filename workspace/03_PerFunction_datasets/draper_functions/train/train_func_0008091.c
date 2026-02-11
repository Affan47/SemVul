ensure_triangle_(const Triangulator *triangulator,
                 gconstpointer points, gsize point_size,
                 Triangle *triangle,
                 const Point *pt)
{
    gboolean moved;
    guint iter;

    iter = 0;
    while (!triangle_contains_point(triangle, pt)) {
        if (triangle->da <= triangle->db) {
            if (triangle->da <= triangle->dc)
                moved = move_triangle_a_(triangulator, points, point_size,
                                         triangle);
            else
                moved = move_triangle_c_(triangulator, points, point_size,
                                         triangle);
        }
        else {
            if (triangle->db <= triangle->dc)
                moved = move_triangle_b_(triangulator, points, point_size,
                                         triangle);
            else
                moved = move_triangle_c_(triangulator, points, point_size,
                                         triangle);
        }

        if (!moved)
            return FALSE;

        make_triangle(triangle, points, point_size);
        if (G_UNLIKELY(iter++ == triangulator->npoints)) {
            triangle->ia = triangle->ib = triangle->ic = UNDEF;
            return FALSE;
        }
    }

    return TRUE;
}
