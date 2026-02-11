gx_default_put_icc_colorants(gs_param_string *colorants, gx_device * dev)
{
    char *tempstr;
    int code;

    if (colorants->size == 0) return 0;


    fill_dev_proc(dev, get_profile, gx_default_get_profile);
    tempstr = (char *) gs_alloc_bytes(dev->memory, colorants->size+1,
                                      "gx_default_put_icc_colorants");
    memcpy(tempstr, colorants->data, colorants->size);

    tempstr[colorants->size] = 0;
    code = gsicc_set_device_profile_colorants(dev, tempstr);
    gs_free_object(dev->memory, tempstr, "gx_default_put_icc_colorants");
    return code;
}
