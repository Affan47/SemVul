gx_forward_fillpage(gx_device *dev, gs_imager_state * pis, gx_device_color *pdevc)
{
    gx_device_forward * const fdev = (gx_device_forward *)dev;
    gx_device *tdev = fdev->target;
    dev_proc_fillpage((*proc)) =
        (tdev == 0 ? (tdev = dev, gx_default_fillpage) :
         dev_proc(tdev, fillpage));
    return proc(tdev, pis, pdevc);
}
