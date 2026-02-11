pclxl_close_device(gx_device * dev)
{
    gx_device_pclxl *const xdev = (gx_device_pclxl *)dev;
    FILE *file = xdev->file;

    if (xdev->strm != NULL)
        sflush(xdev->strm);
    if (xdev->in_page)
        fputc(pxtEndPage, file);
    px_write_file_trailer(file);
    return gdev_vector_close_file((gx_device_vector *)dev);
}
