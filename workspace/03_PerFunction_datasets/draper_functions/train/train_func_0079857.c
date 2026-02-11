png_get_params_downscale_mfs(gx_device *dev, gs_param_list *plist)
{
    gx_device_png *pdev = (gx_device_png *)dev;
    int code, ecode;

    ecode = 0;
    if ((code = param_write_int(plist, "MinFeatureSize", &pdev->min_feature_size)) < 0)
        ecode = code;
    code = png_get_params_downscale(dev, plist);
    if (code < 0)
        ecode = code;

    return ecode;
}
