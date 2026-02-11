lcvd_fill_rectangle_shifted2(gx_device *dev, int x, int y, int width, int height, gx_color_index color)
{
    pdf_lcvd_t *cvd = (pdf_lcvd_t *)dev;
    int code;

    code = (*dev_proc(cvd->mask, fill_rectangle))((gx_device *)cvd->mask,
        x - cvd->mdev.mapped_x, y - cvd->mdev.mapped_y, width, height, (gx_color_index)1);
    if (code < 0)
        return code;
    return cvd->std_fill_rectangle((gx_device *)&cvd->mdev,
        x - cvd->mdev.mapped_x, y - cvd->mdev.mapped_y, width, height, color);
}
