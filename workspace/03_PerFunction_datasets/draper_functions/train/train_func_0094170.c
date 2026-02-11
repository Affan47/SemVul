gs_image_begin_typed(const gs_image_common_t * pic, gs_state * pgs,
                     bool uses_color, gx_image_enum_common_t ** ppie)
{
    gx_device *dev = gs_currentdevice(pgs);
    gx_clip_path *pcpath;
    int code = gx_effective_clip_path(pgs, &pcpath);
    gx_device *dev2 = dev;
    gx_device_color dc_temp, *pdevc = gs_currentdevicecolor_inline(pgs);

    if (code < 0)
        return code;

    dev_proc(pgs->device, set_graphics_type_tag)(pgs->device, GS_IMAGE_TAG);

    if (uses_color) {
        code = gx_set_dev_color(pgs);
        if (code != 0)
            return code;
        code = gs_state_color_load(pgs);
        if (code < 0)
            return code;
    }


    if (pic->type->begin_typed_image == &gx_begin_image1) {
        gs_image_t *image = (gs_image_t *)pic;

        if(image->ImageMask) {
            code = gx_image_fill_masked_start(dev, gs_currentdevicecolor_inline(pgs), pcpath, pgs->memory, &dev2);
            if (code < 0)
                return code;
        }
        if (dev2 != dev) {
            set_nonclient_dev_color(&dc_temp, 1);
            pdevc = &dc_temp;
        }
    }
    code = gx_device_begin_typed_image(dev2, (const gs_imager_state *)pgs,
                NULL, pic, NULL, pdevc, pcpath, pgs->memory, ppie);
    if (code < 0)
        return code;
    code = is_image_visible(pic, pgs, pcpath);
    if (code < 0)
        return code;
    if (!code)
        (*ppie)->skipping = true;
    return 0;
}
