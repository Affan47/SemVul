HexConvert_US8(HexDialogVal64 *val, HexConversionProperties *prop)
{
    int i, local = 0;
    for (i = 0; i < 8; i++)
        local += ((val->v[0] >> i) & 0x1) * pow2(i);

    if (!prop->hexHint)
        snprintf(convbuffer, sizeof(convbuffer), "%u", local);
    else
        snprintf(convbuffer, sizeof(convbuffer), "0x%02X", local);
    return convbuffer;
}
