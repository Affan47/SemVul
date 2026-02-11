fileCorruptByMutation(const char  *filein,
                      l_float32    loc,
                      l_float32    size,
                      const char  *fileout)
{
l_int32   i, locb, sizeb;
size_t    bytes;
l_uint8  *data;

    PROCNAME("fileCorruptByMutation");

    if (!filein || !fileout)
        return ERROR_INT("filein and fileout not both specified", procName, 1);
    if (loc < 0.0 || loc >= 1.0)
        return ERROR_INT("loc must be in [0.0 ... 1.0)", procName, 1);
    if (size <= 0.0)
        return ERROR_INT("size must be > 0.0", procName, 1);
    if (loc + size > 1.0)
        size = 1.0 - loc;

    data = l_binaryRead(filein, &bytes);
    locb = (l_int32)(loc * bytes + 0.5);
    locb = L_MIN(locb, bytes - 1);
    sizeb = (l_int32)(size * bytes + 0.5);
    sizeb = L_MAX(1, sizeb);
    sizeb = L_MIN(sizeb, bytes - locb);
    L_INFO("Randomizing %d bytes at location %d\n", procName, sizeb, locb);


    for (i = 0; i < sizeb; i++) {
        data[locb + i] =
            (l_uint8)(255.9 * ((l_float64)rand() / (l_float64)RAND_MAX));
    }

    l_binaryWrite(fileout, "w", data, bytes);
    FREE(data);
    return 0;
}
