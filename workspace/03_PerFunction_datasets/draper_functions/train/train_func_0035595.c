parse_data_block(INT64 offset, unsigned char *buf, size_t buf_size)
{

    UINT64 dataLen = 0;
    UINT64 dataUnc = 0;

    if (!strncmp((char *)buf, "DATA", 4))
        printf("\ngzip data block found at offset %lld\n", offset);
    else
        printf("\nbzip2 data block found at offset %lld\n", offset);

    dataLen = (UINT64)buf[4];
    dataLen |= (UINT64)buf[5] << 8;
    dataLen |= (UINT64)buf[6] << 16;
    dataLen |= (UINT64)buf[7] << 24;
    dataLen |= (UINT64)buf[8] << 32;
    dataLen |= (UINT64)buf[9] << 40;
    printf("  compressed block size %llu bytes\n", dataLen);

    dataUnc = (UINT64)buf[10];
    dataUnc |= (UINT64)buf[11] << 8;
    dataUnc |= (UINT64)buf[12] << 16;
    dataUnc |= (UINT64)buf[13] << 24;
    dataUnc |= (UINT64)buf[14] << 32;
    dataUnc |= (UINT64)buf[15] << 40;
    printf("  uncompressed block size %llu bytes\n", dataUnc);

    return dataLen;
}
