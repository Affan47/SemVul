cs_next_array_value(shade_coord_stream_t * cs, int num_bits, uint * pvalue)
{
    float value;
    uint read;

    if (sgets(cs->s, (byte *)&value, sizeof(float), &read) < 0 ||
        read != sizeof(float)) {
        cs->ds_EOF = true;
        return_error(gs_error_rangecheck);
    }
    if (value < 0 || (num_bits != 0 && num_bits < sizeof(uint) * 8 &&
         value >= (1 << num_bits)) ||
        value != (uint)value
        )
        return_error(gs_error_rangecheck);
    *pvalue = (uint) value;
    return 0;
}
