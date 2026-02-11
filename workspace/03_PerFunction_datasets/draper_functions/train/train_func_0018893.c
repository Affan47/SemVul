get_rinkj_color_mapping_procs(const gx_device * dev)
{
    const rinkj_device *rdev = (const rinkj_device *)dev;

    if (rdev->color_model == RINKJ_DEVICE_RGB)
        return &spotRGB_procs;
    else if (rdev->color_model == RINKJ_DEVICE_CMYK)
        return &spotCMYK_procs;
    else if (rdev->color_model == RINKJ_DEVICE_N)
        return &spotN_procs;
    else
        return NULL;
}
