gdev_vector_fill_trapezoid(gx_device * dev, const gs_fixed_edge * left,
        const gs_fixed_edge * right, fixed ybot, fixed ytop, bool swap_axes,
                  const gx_device_color * pdevc, gs_logical_operation_t lop)
{
    fixed xl = left->start.x;
    fixed wl = left->end.x - xl;
    fixed yl = left->start.y;
    fixed hl = left->end.y - yl;
    fixed xr = right->start.x;
    fixed wr = right->end.x - xr;
    fixed yr = right->start.y;
    fixed hr = right->end.y - yr;
    fixed x0l = xl + fixed_mult_quo(wl, ybot - yl, hl);
    fixed x1l = xl + fixed_mult_quo(wl, ytop - yl, hl);
    fixed x0r = xr + fixed_mult_quo(wr, ybot - yr, hr);
    fixed x1r = xr + fixed_mult_quo(wr, ytop - yr, hr);

#define y0 ybot
#define y1 ytop
    int code = update_fill(vdev, NULL, pdevc, lop);
    gs_fixed_point points[4];

    if (code < 0)
        return gx_default_fill_trapezoid(dev, left, right, ybot, ytop,
                                         swap_axes, pdevc, lop);

    code = gdev_vector_update_clip_path(vdev, NULL);
    if (code < 0)
        return code;
    if (swap_axes)
        points[0].y = x0l, points[1].y = x0r,
            points[0].x = points[1].x = y0,
            points[2].y = x1r, points[3].y = x1l,
            points[2].x = points[3].x = y1;
    else
        points[0].x = x0l, points[1].x = x0r,
            points[0].y = points[1].y = y0,
            points[2].x = x1r, points[3].x = x1l,
            points[2].y = points[3].y = y1;
#undef y0
#undef y1
    if (vdev->bbox_device) {
        int code = (*dev_proc(vdev->bbox_device, fill_trapezoid))
        ((gx_device *) vdev->bbox_device, left, right, ybot, ytop,
         swap_axes, pdevc, lop);

        if (code < 0)
            return code;
    }
    return gdev_vector_write_polygon(vdev, points, 4, true,
                                     gx_path_type_fill);
}
