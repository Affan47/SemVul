gx_default_put_usefastcolor(bool fastcolor, gx_device * dev)
{
    int code = 0;
    cmm_dev_profile_t *profile_struct;

    if (dev->procs.get_profile == NULL) {


        if (dev->icc_struct == NULL) {

            dev->icc_struct = gsicc_new_device_profile_array(dev->memory);
            if (dev->icc_struct == NULL)
                return_error(gs_error_VMerror);
        }
        dev->icc_struct->usefastcolor = fastcolor;
    } else {
        code = dev_proc(dev, get_profile)(dev,  &profile_struct);
        if (profile_struct == NULL) {

            dev->icc_struct = gsicc_new_device_profile_array(dev->memory);
            profile_struct =  dev->icc_struct;
            if (profile_struct == NULL)
                return_error(gs_error_VMerror);
        }
        profile_struct->usefastcolor = fastcolor;
    }
    return code;
}
