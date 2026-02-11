gray_cs_to_spotrgb_cm(gx_device * dev, frac gray, frac out[])
{

    int i = ((rinkj_device *)dev)->separation_names.num_names;

    out[0] = out[1] = out[2] = gray;
    for(; i>0; i--)
        out[2 + i] = 0;
}
