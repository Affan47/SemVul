HexConvert_S8(HexDialogVal64 *val, HexConversionProperties *prop)
{
    int i, local = 0;
    for (i = 0; i < 7; i++)
        local += ((val->v[0] >> i) & 0x1) * pow2(i);
    if ((val->v[0] >> 7) & 0x1)
        local  = -(pow2(7) - local);
    snprintf(convbuffer, sizeof(convbuffer), "%d", local);
    return convbuffer;
}
