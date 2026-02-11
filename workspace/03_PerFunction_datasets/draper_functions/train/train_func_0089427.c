VerifyAPDUValidStructure(uchar* inBuf, int inBufLen) {
    int lc, dataLen;

    if (inBufLen <= 3)
        return MEM_CARD_ERROR_CMD_STRUCT;


    if (inBufLen == 4)
        return ASE_OK;


    if (inBufLen == 5)
        return ASE_OK;


    lc = inBuf[4];
    if (lc == 0x00)
        return MEM_CARD_ERROR_CMD_STRUCT;
    dataLen = inBufLen - 5;

    if (dataLen != lc && dataLen != (lc + 1))
        return MEM_CARD_ERROR_CMD_STRUCT;

    return ASE_OK;
}
