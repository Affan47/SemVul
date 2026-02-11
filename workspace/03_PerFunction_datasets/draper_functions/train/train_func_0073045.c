tiffscaled8_print_page(gx_device_printer * pdev, FILE * file)
{
    gx_device_tiff *const tfdev = (gx_device_tiff *)pdev;
    int code;

    code = gdev_tiff_begin_page(tfdev, file);
    if (code < 0)
        return code;

    tiff_set_gray_fields(pdev, tfdev->tif, 8, tfdev->Compression, tfdev->MaxStripSize);

    return tiff_downscale_and_print_page(pdev, tfdev->tif,
                                         tfdev->DownScaleFactor,
                                         tfdev->MinFeatureSize,
                                         tfdev->AdjustWidth,
                                         8, 1);
}
