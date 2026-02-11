pdf14_gray_cs_to_cmyk_cm(gx_device * dev, frac gray, frac out[])
{
    int num_comp = dev->color_info.num_components;

    out[0] = out[1] = out[2] = frac_0;
    out[3] = frac_1 - gray;
    for (--num_comp; num_comp > 3; num_comp--)
        out[num_comp] = 0;
}
