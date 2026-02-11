gx_render_device_DeviceN(frac * pcolor,
        gx_device_color * pdevc, gx_device * dev,
        gx_device_halftone * pdht, const gs_int_point * ht_phase)
{
    uint max_value[GS_CLIENT_COLOR_MAX_COMPONENTS];
    frac dither_check = 0;
    uint int_color[GS_CLIENT_COLOR_MAX_COMPONENTS];
    gx_color_value vcolor[GS_CLIENT_COLOR_MAX_COMPONENTS];
    int i;
    int num_colors = dev->color_info.num_components;
    uint l_color[GS_CLIENT_COLOR_MAX_COMPONENTS];

    for (i=0; i<num_colors; i++) {
        max_value[i] = (dev->color_info.gray_index == i) ?
             dev->color_info.dither_grays - 1 :
             dev->color_info.dither_colors - 1;
    }

    for (i = 0; i < num_colors; i++) {
        unsigned long hsize = pdht ?
                (unsigned) pdht->components[i].corder.num_levels
                : 1;
        unsigned long nshades = hsize * max_value[i] + 1;
        long shade = pcolor[i] * nshades / (frac_1_long + 1);
        int_color[i] = shade / hsize;
        l_color[i] = shade % hsize;
        if (max_value[i] < MIN_CONTONE_LEVELS)
            dither_check |= l_color[i];
    }

#ifdef DEBUG
    if (gs_debug_c('c')) {
        dmlprintf1(dev->memory, "[c]ncomp=%d ", num_colors);
        for (i = 0; i < num_colors; i++)
            dmlprintf1(dev->memory, "0x%x, ", pcolor[i]);
        dmlprintf(dev->memory, "-->   ");
        for (i = 0; i < num_colors; i++)
            dmlprintf2(dev->memory, "%x+0x%x, ", int_color[i], l_color[i]);
        dmlprintf(dev->memory, "\n");
    }
#endif


    if (!dither_check) {
        for (i = 0; i < num_colors; i++)
            vcolor[i] = fractional_color(int_color[i], max_value[i]);
        color_set_pure(pdevc, dev_proc(dev, encode_color)(dev, vcolor));
        return 0;
    }


    for (i = 0; i < num_colors; i++)
        _color_set_c(pdevc, i, int_color[i], l_color[i]);
    gx_complete_halftone(pdevc, num_colors, pdht);

    color_set_phase_mod(pdevc, ht_phase->x, ht_phase->y,
                            pdht->lcm_width, pdht->lcm_height);


    if (!(pdevc->colors.colored.plane_mask &
         (pdevc->colors.colored.plane_mask - 1))) {

        return gx_devn_reduce_colored_halftone(pdevc, dev);
    }

    return 1;
}
