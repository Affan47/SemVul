psw_copy_mono(gx_device * dev, const byte * data,
        int data_x, int raster, gx_bitmap_id id, int x, int y, int w, int h,
              gx_color_index zero, gx_color_index one)
{
    gx_device_vector *const vdev = (gx_device_vector *)dev;
    gx_device_pswrite *const pdev = (gx_device_pswrite *)vdev;
    gx_drawing_color color;
    const char *op;
    int code = 0;

    CHECK_BEGIN_PAGE(pdev);
    if (w <= 0 || h <= 0)
        return 0;
    (*dev_proc(vdev->bbox_device, copy_mono))
        ((gx_device *) vdev->bbox_device, data, data_x, raster, id,
         x, y, w, h, zero, one);
    if (one == gx_no_color_index) {
        set_nonclient_dev_color(&color, zero);
        code = gdev_vector_update_fill_color((gx_device_vector *) pdev,
                                             NULL, &color);
        op = "If";
    } else if (zero == vdev->black && one == vdev->white)
        op = "1 I";
    else {
        if (zero != gx_no_color_index) {
            code = (*dev_proc(dev, fill_rectangle)) (dev, x, y, w, h, zero);
            if (code < 0)
                return code;
        }
        set_nonclient_dev_color(&color, one);
        code = gdev_vector_update_fill_color((gx_device_vector *) pdev,
                                             NULL, &color);
        op = ",";
    }
    if (code < 0)
        return 0;
    code = gdev_vector_update_clip_path(vdev, NULL);
    if (code < 0)
        return code;
    return psw_image_write(pdev, op, data, data_x, raster, id,
                           x, y, w, h, 1);
}
