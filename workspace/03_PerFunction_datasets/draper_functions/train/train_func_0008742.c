hl1250_get_params(gx_device * pdev, gs_param_list * plist)
{
    gx_device_hl1250 *hl1250 = (gx_device_hl1250 *) pdev;
    int code, val;

    code = gdev_prn_get_params(pdev, plist);
    if (code < 0)
        return code;
    val = hl1250->econo_mode;
    code = param_write_int(plist, "EconoMode", &val);
    if (code < 0)
        return code;
    val = hl1250->paper_type;
    code = param_write_int(plist, "PaperType", &val);
    if (code < 0)
        return code;
    val = hl1250->source_tray;
    code = param_write_int(plist, "SourceTray", &val);
    return code;
}
