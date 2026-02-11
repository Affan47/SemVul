sep1_fill_path(gx_device * pdev, const gs_imager_state * pis,
                 gx_path * ppath, const gx_fill_params * params,
                 const gx_device_color * pdevc, const gx_clip_path * pcpath)
{
    tiffsep1_device * const tfdev = (tiffsep1_device *)pdev;


    if( tfdev->thresholds[0].dstart == NULL) {
        int code = sep1_ht_order_to_thresholds(pdev, pis);

        if (code < 0)
            return code;
    }
    return (tfdev->fill_path)( pdev, pis, ppath, params, pdevc, pcpath);
}
