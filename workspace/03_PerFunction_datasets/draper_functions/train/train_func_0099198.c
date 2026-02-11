tiffsep_close_comp_file(tiffsep_device *tfdev, const char *fn)
{
    int code;

    if (tfdev->tiff_comp) {
        TIFFCleanup(tfdev->tiff_comp);
        tfdev->tiff_comp = NULL;
    }

    code = gx_device_close_output_file((gx_device *)tfdev,
                                       fn,
                                       tfdev->comp_file);
    tfdev->comp_file = NULL;

    return code;
}
