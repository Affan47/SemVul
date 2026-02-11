pdf14_unpack_additive(int num_comp, gx_color_index color,
                                pdf14_device * p14dev, byte * out)
{
    int i;

    for (i = num_comp - 1; i >= 0; i--) {
        out[i] = (byte)(color & 0xff);
        color >>= 8;
    }
}
