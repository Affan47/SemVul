gx_devn_read_color(
    ushort              values[],
    const gx_device *   dev,
    const byte *        pdata,
    int                 size )
{
    gx_color_index      mask = 0;
    int                 i;
    int                 ncomps = dev->color_info.num_components;
    int                 pos;
    int                 num_bytes;


    if (size < 1)
        return_error(gs_error_rangecheck);


    for (i = 0; i < sizeof(gx_color_index); i++)
        mask = (mask << 8) | pdata[i];
    pos = i;
    num_bytes = i;

    for (i = 0; i < ncomps; i++) {
        if (mask & 1) {
            values[i] = pdata[pos];
            pos++;
            values[i] += (pdata[pos]<<8);
            pos++;
            num_bytes += 2;
        } else {
            values[i] = 0;
        }
        mask >>= 1;
    }
    return num_bytes;
}
