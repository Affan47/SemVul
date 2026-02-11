rinkj_decode_color(gx_device * dev, gx_color_index color, gx_color_value * out)
{
    int bpc = ((rinkj_device *)dev)->bitspercomponent;
    int drop = sizeof(gx_color_value) * 8 - bpc;
    int mask = (1 << bpc) - 1;
    int i = 0;
    int ncomp = dev->color_info.num_components;

    for (; i<ncomp; i++) {
        out[ncomp - i - 1] = (color & mask) << drop;
        color >>= bpc;
    }
    return 0;
}
