LoadUnicodeName  (HPDF_Stream   stream,
                  HPDF_UINT     offset,
                  HPDF_UINT     len,
                  char    *buf)
{
    HPDF_BYTE tmp[HPDF_LIMIT_MAX_NAME_LEN * 2 + 1];
    HPDF_UINT i = 0;
    HPDF_UINT j = 0;
    HPDF_STATUS ret;

    HPDF_MemSet (buf, 0, HPDF_LIMIT_MAX_NAME_LEN + 1);

    if ((ret = HPDF_Stream_Seek (stream, offset, HPDF_SEEK_SET)) !=
            HPDF_OK)
        return ret;

    if ((ret = HPDF_Stream_Read (stream, tmp, &len))
             != HPDF_OK)
        return ret;

    while (i < len) {
        i++;
        buf[j] = tmp[i];
        j++;
        i++;
    }

    return HPDF_OK;
}
