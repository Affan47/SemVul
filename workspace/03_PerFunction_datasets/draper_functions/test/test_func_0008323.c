gdev_prn_size_buf_planar(gx_device_buf_space_t *space, gx_device *target,
                         const gx_render_plane_t *render_plane,
                         int height, bool for_band)
{
    gx_device_memory mdev;
    int code;

    if (render_plane && render_plane->index >= 0)
        return gx_default_size_buf_device(space, target, render_plane,
                                          height, for_band);
    mdev.color_info = target->color_info;
    code = gdev_prn_set_planar(&mdev, target);
    if (code < 0)
        return code;
    if (gdev_mem_bits_size(&mdev, target->width, height, &(space->bits)) < 0)
        return_error(gs_error_VMerror);
    space->line_ptrs = gdev_mem_line_ptrs_size(&mdev, target->width, height);
    space->raster = bitmap_raster(target->width * mdev.planes[0].depth);
    return 0;
}
