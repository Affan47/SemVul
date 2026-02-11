pixcmapConvertToHex(l_uint8 *data,
                    l_int32  nbytes,
                    l_int32  ncolors)
{
l_int32  i, j, hexbytes;
l_int32  cpc;
char    *hexdata = NULL;
char     buf[4];

    PROCNAME("pixcmapConvertToHex");

    if (!data)
        return (char *)ERROR_PTR("data not defined", procName, NULL);
    if (ncolors < 1)
        return (char *)ERROR_PTR("no colors", procName, NULL);

    cpc = nbytes / ncolors;
    if (cpc != 3 && cpc != 4)
        return (char *)ERROR_PTR("cpc not 3 or 4", procName, NULL);

    hexbytes = 2 + (2 * cpc + 1) * ncolors + 2;
    hexdata = (char *)CALLOC(hexbytes, sizeof(char));
    hexdata[0] = '<';
    hexdata[1] = ' ';

    for (i = 0; i < ncolors; i++) {
        j = 2 + (2 * cpc + 1) * i;
        snprintf(buf, sizeof(buf), "%02x", data[cpc * i]);
        hexdata[j] = buf[0];
        hexdata[j + 1] = buf[1];
        snprintf(buf, sizeof(buf), "%02x", data[cpc * i + 1]);
        hexdata[j + 2] = buf[0];
        hexdata[j + 3] = buf[1];
        snprintf(buf, sizeof(buf), "%02x", data[cpc * i + 2]);
        hexdata[j + 4] = buf[0];
        hexdata[j + 5] = buf[1];
        hexdata[j + 6] = ' ';
    }
    hexdata[j + 7] = '>';
    hexdata[j + 8] = '\0';
    return hexdata;
}
