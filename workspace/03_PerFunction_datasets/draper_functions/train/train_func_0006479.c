pc_4bit_map_rgb_color(gx_device * dev, const gx_color_value cv[])
{
    gx_color_index r, g, color;

    r = (cv[0] > (gx_max_color_value/2));
    g = (cv[1] > (gx_max_color_value/2));
    color = (cv[2] > (gx_max_color_value/2));
    color += (r << 2) + (g << 1);
    if (color > 0)
        color += 8;
    return color;
}
