pclxl_set_color(gx_device_pclxl * xdev, const gx_drawing_color * pdc,
                px_attribute_t null_source, px_tag_t op)
{
    stream *s = pclxl_stream(xdev);

    if (gx_dc_is_pure(pdc)) {
        gx_color_index color = gx_dc_pure_color(pdc);

        if (op == pxtSetPenSource)   xdev->pen_null   = false;
        if (op == pxtSetBrushSource) xdev->brush_null = false;

        if (xdev->color_info.num_components == 1 || RGB_IS_GRAY(color)) {
            pclxl_set_color_space(xdev, eGray);
            px_put_uba(s, (byte) color, pxaGrayLevel);
        } else {
            pclxl_set_color_space(xdev, eRGB);
            spputc(s, pxt_ubyte_array);
            px_put_ub(s, 3);
            spputc(s, (byte) (color >> 16));
            spputc(s, (byte) (color >> 8));
            spputc(s, (byte) color);
            px_put_a(s, pxaRGBColor);
        }
    } else if (gx_dc_is_null(pdc) || !color_is_set(pdc)) {
        if (op == pxtSetPenSource || op == pxtSetBrushSource)
            return pclxl_set_cached_nulls(xdev, null_source, op);
        else
            px_put_uba(s, 0, null_source);
    } else
        return_error(gs_error_rangecheck);
    spputc(s, (byte)op);
    return 0;
}
