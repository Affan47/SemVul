pclxl_set_color_space(gx_device_pclxl * xdev, pxeColorSpace_t color_space)
{
    if (xdev->color_space != color_space) {
        stream *s = pclxl_stream(xdev);

        px_put_ub(s, (byte)color_space);
        px_put_ac(s, pxaColorSpace, pxtSetColorSpace);
        xdev->color_space = color_space;
        xdev->palette.size = 0;
    }
}
