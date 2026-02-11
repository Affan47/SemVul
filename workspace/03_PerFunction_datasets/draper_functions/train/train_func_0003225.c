gx_default_encode_color(gx_device * dev, const gx_color_value cv[])
{
    int             ncomps = dev->color_info.num_components;
    int             i;
    const byte *    comp_shift = dev->color_info.comp_shift;
    const byte *    comp_bits = dev->color_info.comp_bits;
    gx_color_index  color = 0;

#ifdef DEBUG
    if ( dev->color_info.separable_and_linear != GX_CINFO_SEP_LIN ) {
        dmprintf(dev->memory, "gx_default_encode_color() requires separable and linear\n" );
        return gx_no_color_index;
    }
#endif
    for (i = 0; i < ncomps; i++) {
        COLROUND_VARS;
        COLROUND_SETUP(comp_bits[i]);
        color |= COLROUND_ROUND(cv[i]) << comp_shift[i];

    }
    return color;
}
