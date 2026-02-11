cmyk_cs_to_psdrgb_cm(gx_device * dev,
                        frac c, frac m, frac y, frac k, frac out[])
{
    int i = ((psd_device *)dev)->devn_params.separations.num_separations;

    color_cmyk_to_rgb(c, m, y, k, NULL, out, dev->memory);
    for(; i>0; i--)
        out[2 + i] = 0;
}
