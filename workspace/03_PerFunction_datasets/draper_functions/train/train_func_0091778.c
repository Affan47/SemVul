pdf_make_mxd(gx_device **pmxdev, gx_device *tdev, gs_memory_t *mem)
{
    gx_device *fdev;
    int code = gs_copydevice(&fdev, (const gx_device *)&gs_null_device, mem);

    if (code < 0)
        return code;
    gx_device_set_target((gx_device_forward *)fdev, tdev);
    *pmxdev = fdev;
    return 0;
}
