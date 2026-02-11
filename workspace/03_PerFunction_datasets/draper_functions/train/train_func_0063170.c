devn_decode_compressed_color(gx_device * dev, gx_color_index color,
                        gx_color_value * out, gs_devn_params * pdevn_params)
{
    int comp_num = 0;
    int factor, bit_count, bit_mask;
    int ncomp = dev->color_info.num_components;
    comp_bit_map_list_t * pbitmap;
    gx_color_value solid_color = gx_max_color_value;


    if (color == NON_ENCODEABLE_COLOR) {
        for (; comp_num < ncomp; comp_num++)
            out[comp_num] = gx_max_color_value;
        return 0;
    }
    pbitmap = find_bit_map(color, pdevn_params->compressed_color_list);
    bit_count = num_comp_bits[pbitmap->num_non_solid_comp];
    bit_mask = (1 << bit_count) - 1;
    factor = comp_bit_factor[pbitmap->num_non_solid_comp];
    if (pbitmap->solid_not_100) {
        solid_color = (factor * ((int)color & bit_mask)) >> 8;
        color >>= bit_count;
    }
    for (; comp_num < ncomp; comp_num++) {
        if (colorant_present(pbitmap, colorants, comp_num)) {
            if (colorant_present(pbitmap, solid_colorants, comp_num))
                out[comp_num] = solid_color;
            else {
                out[comp_num] = (factor * ((int)color & bit_mask)) >> 8;
                color >>= bit_count;
            }
        }
        else
            out[comp_num] = 0;
    }
    return 0;
}
