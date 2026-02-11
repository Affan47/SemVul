gx_devn_write_color(
    const gx_device_color *pdevc,
    const gx_device *   dev,
    byte *              pdata,
    uint *              psize )
{
    int                 num_bytes1, num_bytes_temp, num_bytes;
    gx_color_index      mask, mask_temp;
    int                 count;
    int                 i, ncomps = dev->color_info.num_components;


    count = gx_dc_devn_get_nonzero_comps(pdevc, dev, &mask);
    num_bytes1 = sizeof(gx_color_index);
    num_bytes = num_bytes1 + count * 2;
    num_bytes_temp = num_bytes1;


    if (*psize < num_bytes) {
        *psize = num_bytes;
        return_error(gs_error_rangecheck);
    }
    *psize = num_bytes;

    mask_temp = mask;
    while (--num_bytes1 >= 0) {
        pdata[num_bytes1] = mask_temp & 0xff;
        mask_temp >>= 8;
    }

    for (i = 0; i < ncomps; i++) {
        if (mask & 1) {
            pdata[num_bytes_temp] = pdevc->colors.devn.values[i] & 0xff;
            num_bytes_temp++;
            pdata[num_bytes_temp] = (pdevc->colors.devn.values[i] >> 8) & 0xff;
            num_bytes_temp++;
        }
        mask >>= 1;
    }
    return 0;
}
