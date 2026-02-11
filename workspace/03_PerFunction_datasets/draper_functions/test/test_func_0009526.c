clist_fill_linear_color_triangle(gx_device * dev, const gs_fill_attributes *fa,
        const gs_fixed_point *p0, const gs_fixed_point *p1,
        const gs_fixed_point *p2,
        const frac31 *c0, const frac31 *c1, const frac31 *c2)
{
    gs_fixed_edge left, right;
    int code;

    left.start = *p0;
    left.end = *p1;
    right.start = *p2;
    right.end.x = right.end.y = 0;

    code = clist_write_fill_trapezoid(dev, &left, &right,
        0, 0, fa->swap_axes | 2 | 4, NULL, fa->lop, fa, c0, c1, c2, NULL);
    if (code < 0)
        return code;


    return 1;
}
