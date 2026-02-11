pass_shading_area_through_clip_path_device(gx_device * pdev, const gs_imager_state * pis,
                     gx_path * ppath, const gx_fill_params * params,
                 const gx_device_color * pdevc, const gx_clip_path * pcpath)
{
    if (pdevc == NULL) {
        gx_device_clip *cdev = (gx_device_clip *)pdev;

        return dev_proc(cdev->target, fill_path)(cdev->target, pis, ppath, params, pdevc, pcpath);
    }

    return gx_default_fill_path(pdev, pis, ppath, params, pdevc, pcpath);
}
