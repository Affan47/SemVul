build_cmyk_raster_line_fromplanar_1bpc(gs_get_bits_params_t params, byte * dest,
                                       int width, int num_comp,
                                       cmyk_composite_map * cmyk_map, int num_order,
                                       tiffsep_device * const tfdev)
{
    int pixel, comp_num;
    uint temp, cyan, magenta, yellow, black;
    cmyk_composite_map * cmyk_map_entry;

    for (pixel = 0; pixel < width; pixel++) {
        cmyk_map_entry = cmyk_map;
        temp = *(params.data[tfdev->devn_params.separation_order_map[0]] + (pixel>>3));
        temp = ((temp<<(pixel & 7))>>7) & 1;
        cyan = cmyk_map_entry->c * temp;
        magenta = cmyk_map_entry->m * temp;
        yellow = cmyk_map_entry->y * temp;
        black = cmyk_map_entry->k * temp;
        cmyk_map_entry++;
        for (comp_num = 1; comp_num < num_comp; comp_num++) {
            temp =
                *(params.data[tfdev->devn_params.separation_order_map[comp_num]] + (pixel>>3));
            temp = ((temp<<(pixel & 7))>>7) & 1;
            cyan += cmyk_map_entry->c * temp;
            magenta += cmyk_map_entry->m * temp;
            yellow += cmyk_map_entry->y * temp;
            black += cmyk_map_entry->k * temp;
            cmyk_map_entry++;
        }
        cyan /= frac_1;
        magenta /= frac_1;
        yellow /= frac_1;
        black /= frac_1;
        if (cyan > 1)
            cyan = 1;
        if (magenta > 1)
            magenta = 1;
        if (yellow > 1)
            yellow = 1;
        if (black > 1)
            black = 1;
        if ((pixel & 1) == 0)
            *dest = (cyan<<7) | (magenta<<6) | (yellow<<5) | (black<<4);
        else
            *dest++ |= (cyan<<3) | (magenta<<2) | (yellow<<1) | black;
    }
}
