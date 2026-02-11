display_map_rgb_color_rgb(gx_device * dev, const gx_color_value cv[])
{
    gx_device_display *ddev = (gx_device_display *) dev;
    gx_color_value r = cv[0];
    gx_color_value g = cv[1];
    gx_color_value b = cv[2];
    int drop = gx_color_value_bits - 8;
    gx_color_value red, green, blue;

    red  = r >> drop;
    green = g >> drop;
    blue = b >> drop;

    switch (ddev->nFormat & DISPLAY_ALPHA_MASK) {
        case DISPLAY_ALPHA_NONE:
            if ((ddev->nFormat & DISPLAY_ENDIAN_MASK) == DISPLAY_BIGENDIAN) {
                gx_color_value rgb[3];
                rgb[0] = r; rgb[1] = g; rgb[2] = b;
                return gx_default_rgb_map_rgb_color(dev, rgb);
            }
            else
                return (blue<<16) + (green<<8) + red;
        case DISPLAY_ALPHA_FIRST:
        case DISPLAY_UNUSED_FIRST:
            if ((ddev->nFormat & DISPLAY_ENDIAN_MASK) == DISPLAY_BIGENDIAN)
                return ((gx_color_index)red<<16) + (green<<8) + blue;
            else
                return ((gx_color_index)blue<<16) + (green<<8) + red;
        case DISPLAY_ALPHA_LAST:
        case DISPLAY_UNUSED_LAST:
            if ((ddev->nFormat & DISPLAY_ENDIAN_MASK) == DISPLAY_BIGENDIAN)
                return ((gx_color_index)red<<24) + (green<<16) + (blue<<8);
            else
                return ((gx_color_index)blue<<24) + (green<<16) + (red<<8);
    }
    return 0;
}
