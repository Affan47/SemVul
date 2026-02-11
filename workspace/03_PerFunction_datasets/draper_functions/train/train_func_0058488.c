bbox_strip_copy_rop(gx_device * dev,
                    const byte * sdata, int sourcex, uint sraster,
                    gx_bitmap_id id,
                    const gx_color_index * scolors,
                    const gx_strip_bitmap * textures,
                    const gx_color_index * tcolors,
                    int x, int y, int w, int h,
                    int phase_x, int phase_y, gs_logical_operation_t lop)
{
    gx_device_bbox *const bdev = (gx_device_bbox *) dev;

    gx_device *tdev = bdev->target;
    int code =
        (tdev == 0 ? 0 :
         dev_proc(tdev, strip_copy_rop)
         (tdev, sdata, sourcex, sraster, id, scolors,
          textures, tcolors, x, y, w, h, phase_x, phase_y, lop));

    BBOX_ADD_INT_RECT(bdev, x, y, x + w, y + h);
    return code;
}
