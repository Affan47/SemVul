getRGBFromIndex(l_uint32  index,
                l_int32   sigbits,
                l_int32  *prval,
                l_int32  *pgval,
                l_int32  *pbval)
{
    PROCNAME("getRGBFromIndex");

    if (prval) *prval = 0;
    if (pgval) *pgval = 0;
    if (pbval) *pbval = 0;
    if (!prval || !pgval || !pbval)
        return ERROR_INT("not all component ptrs defined", procName, 1);
    if (sigbits < 2 || sigbits > 6)
        return ERROR_INT("sigbits not in [2 ... 6]", procName, 1);

    switch (sigbits) {
    case 2:
        *prval = ((index << 2) & 0xc0) | 0x20;
        *pgval = ((index << 4) & 0xc0) | 0x20;
        *pbval = ((index << 6) & 0xc0) | 0x20;
        break;
    case 3:
        *prval = ((index >> 1) & 0xe0) | 0x10;
        *pgval = ((index << 2) & 0xe0) | 0x10;
        *pbval = ((index << 5) & 0xe0) | 0x10;
        break;
    case 4:
        *prval = ((index >> 4) & 0xf0) | 0x08;
        *pgval = (index & 0xf0) | 0x08;
        *pbval = ((index << 4) & 0xf0) | 0x08;
        break;
    case 5:
        *prval = ((index >> 7) & 0xf8) | 0x04;
        *pgval = ((index >> 2) & 0xf8) | 0x04;
        *pbval = ((index << 3) & 0xf8) | 0x04;
        break;
    case 6:
        *prval = ((index >> 10) & 0xfc) | 0x02;
        *pgval = ((index >> 4) & 0xfc) | 0x02;
        *pbval = ((index << 2) & 0xfc) | 0x02;
        break;
    default:
        L_ERROR("Illegal sigbits = %d\n", procName, sigbits);
        return ERROR_INT("sigbits not in [2 ... 6]", procName, 1);
    }

    return 0;
}
