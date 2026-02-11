gdev_pdf_copy_color(gx_device * dev, const byte * base, int sourcex,
                    int raster, gx_bitmap_id id, int x, int y, int w, int h)
{
    gx_device_pdf *pdev = (gx_device_pdf *) dev;
    gs_image_t image;
    pdf_image_writer writer;
    int code;

    if (w <= 0 || h <= 0)
        return 0;
    code = pdf_open_page(pdev, PDF_IN_STREAM);
    if (code < 0)
        return code;

    code = pdf_put_clip_path(pdev, NULL);
    if (code < 0)
        return code;
    code = pdf_copy_color_data(pdev, base, sourcex, raster, id, x, y, w, h,
                               &image, &writer, 0);
    switch (code) {
        default:
            return code;
        case 1:
            return 0;
        case 0:
            return pdf_do_image(pdev, writer.pres, NULL, true);
    }
}
