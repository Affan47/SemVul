gdev_vector_get_params(gx_device * dev, gs_param_list * plist)
{
    int code = gx_default_get_params(dev, plist);
    int ecode;
    gs_param_string ofns;
    bool bool_true = 1;

    if (code < 0)
        return code;
    ofns.data = (const byte *)vdev->fname,
        ofns.size = strlen(vdev->fname),
        ofns.persistent = false;
    if ((ecode = param_write_string(plist, "OutputFile", &ofns)) < 0)
        return ecode;
    if ((ecode = param_write_bool(plist, "HighLevelDevice", &bool_true)) < 0)
        return ecode;
    return code;
}
