explode(
        unsigned int (*read_buf)(char *buf, unsigned  int *size, void *param),
        void         (*write_buf)(char *buf, unsigned  int *size, void *param),
        char         *work_buf,
        void         *param)
{
    TDcmpStruct * pWork = (TDcmpStruct *)work_buf;


    pWork->read_buf   = read_buf;
    pWork->write_buf  = write_buf;
    pWork->param      = param;
    pWork->in_pos     = sizeof(pWork->in_buff);
    pWork->in_bytes   = pWork->read_buf((char *)pWork->in_buff, &pWork->in_pos, pWork->param);
    if(pWork->in_bytes <= 4)
        return CMP_BAD_DATA;

    pWork->ctype      = pWork->in_buff[0];
    pWork->dsize_bits = pWork->in_buff[1];
    pWork->bit_buff   = pWork->in_buff[2];
    pWork->extra_bits = 0;
    pWork->in_pos     = 3;


    if(4 > pWork->dsize_bits || pWork->dsize_bits > 6)
        return CMP_INVALID_DICTSIZE;

    pWork->dsize_mask = 0xFFFF >> (0x10 - pWork->dsize_bits);

    if(pWork->ctype != CMP_BINARY)
    {
        if(pWork->ctype != CMP_ASCII)
            return CMP_INVALID_MODE;

        memcpy(pWork->ChBitsAsc, ChBitsAsc, sizeof(pWork->ChBitsAsc));
        GenAscTabs(pWork);
    }

    memcpy(pWork->LenBits, LenBits, sizeof(pWork->LenBits));
    GenDecodeTabs(pWork->LengthCodes, LenCode, pWork->LenBits, sizeof(pWork->LenBits));
    memcpy(pWork->ExLenBits, ExLenBits, sizeof(pWork->ExLenBits));
    memcpy(pWork->LenBase, LenBase, sizeof(pWork->LenBase));
    memcpy(pWork->DistBits, DistBits, sizeof(pWork->DistBits));
    GenDecodeTabs(pWork->DistPosCodes, DistCode, pWork->DistBits, sizeof(pWork->DistBits));
    if(Expand(pWork) != 0x306)
        return CMP_NO_ERROR;

    return CMP_ABORT;
}
