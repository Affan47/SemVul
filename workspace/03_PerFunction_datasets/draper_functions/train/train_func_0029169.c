gdev_vector_write_polygon(gx_device_vector * vdev, const gs_fixed_point * points,
                          uint count, bool close, gx_path_type_t type)
{
    int code = 0;

    if (type != gx_path_type_none &&
        (code = (*vdev_proc(vdev, beginpath)) (vdev, type)) < 0
        )
        return code;
    if (count > 0) {
        double x = fixed2float(points[0].x) / vdev->scale.x, y = fixed2float(points[0].y) / vdev->scale.y;
        double x_start = x, y_start = y, x_prev, y_prev;
        uint i;

        code = (*vdev_proc(vdev, moveto))
            (vdev, 0.0, 0.0, x, y, type);
        if (code >= 0)
            for (i = 1; i < count && code >= 0; ++i) {
                x_prev = x, y_prev = y;
                code = (*vdev_proc(vdev, lineto))
                    (vdev, x_prev, y_prev,
                     (x = fixed2float(points[i].x) / vdev->scale.x),
                     (y = fixed2float(points[i].y) / vdev->scale.y),
                     type);
            }
        if (code >= 0 && close)
            code = (*vdev_proc(vdev, closepath))
                (vdev, x, y, x_start, y_start, type);
    }
    return (code >= 0 && type != gx_path_type_none ?
            (*vdev_proc(vdev, endpath)) (vdev, type) : code);
}
