ljet5_close(gx_device * pdev)
{
    gx_device_printer *const ppdev = (gx_device_printer *)pdev;
    int code = gdev_prn_open_printer(pdev, true);

    if (code < 0)
        return code;
    px_write_file_trailer(ppdev->file);
    return gdev_prn_close(pdev);
}
