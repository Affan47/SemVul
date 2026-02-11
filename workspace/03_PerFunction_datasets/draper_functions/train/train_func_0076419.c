mem_planar_fill_rectangle_hl_color(gx_device *dev, const gs_fixed_rect *rect,
    const gs_imager_state *pis, const gx_drawing_color *pdcolor,
    const gx_clip_path *pcpath)
{
    gx_device_memory * const mdev = (gx_device_memory *)dev;
    mem_save_params_t save;
    int pi;
    int x = fixed2int(rect->p.x);
    int y = fixed2int(rect->p.y);
    int w = fixed2int(rect->q.x) - x;
    int h = fixed2int(rect->q.y) - y;


    if (pdcolor->type != gx_dc_type_devn && pdcolor->type != &gx_dc_devn_masked) {
        return gx_fill_rectangle_device_rop( x, y, w, h, pdcolor, dev, lop_default);
    }
    MEM_SAVE_PARAMS(mdev, save);
    for (pi = 0; pi < mdev->num_planes; ++pi) {
        int plane_depth = mdev->planes[pi].depth;
        gx_color_index mask = ((gx_color_index)1 << plane_depth) - 1;
        int shift = 16 - plane_depth;
        const gx_device_memory *mdproto = gdev_mem_device_for_bits(plane_depth);

        MEM_SET_PARAMS(mdev, plane_depth);
        dev_proc(mdproto, fill_rectangle)(dev, x, y, w, h,
                                          (pdcolor->colors.devn.values[pi]) >> shift & mask);
        mdev->line_ptrs += mdev->height;
    }
    MEM_RESTORE_PARAMS(mdev, save);
    return 0;
}
