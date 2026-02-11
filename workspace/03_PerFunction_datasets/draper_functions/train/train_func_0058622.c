gx_image_scale_mask_colors(gx_image_enum *penum, int component_index)
{
    uint scale = 255 / ((1 << penum->bps) - 1);
    uint *values = &penum->mask_color.values[component_index * 2];
    uint v0 = values[0] *= scale;
    uint v1 = values[1] *= scale;

    if (penum->map[component_index].decoding == sd_none &&
        penum->map[component_index].inverted
        ) {
        values[0] = 255 - v1;
        values[1] = 255 - v0;
    }
}
