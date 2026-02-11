gx_forward_upright_get_initial_matrix(gx_device * dev, gs_matrix * pmat)
{
    gx_device_forward * const fdev = (gx_device_forward *)dev;
    gx_device *tdev = fdev->target;

    if (tdev == 0)
        gx_upright_get_initial_matrix(dev, pmat);
    else
        dev_proc(tdev, get_initial_matrix)(tdev, pmat);
}
