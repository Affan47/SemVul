bin_write(UNewDataMemory *mem, struct SResource *res,
                          uint32_t usedOffset, UErrorCode *status) {
    uint32_t pad       = 0;
    uint32_t extrapad  = calcPadding(res->fSize);
    uint32_t dataStart = usedOffset + sizeof(res->u.fBinaryValue.fLength);

    if (dataStart % BIN_ALIGNMENT) {
        pad = (BIN_ALIGNMENT - dataStart % BIN_ALIGNMENT);
        udata_writePadding(mem, pad);
        usedOffset += pad;
    }

    udata_write32(mem, res->u.fBinaryValue.fLength);
    if (res->u.fBinaryValue.fLength > 0) {
        udata_writeBlock(mem, res->u.fBinaryValue.fData, res->u.fBinaryValue.fLength);
    }
    udata_writePadding(mem, (BIN_ALIGNMENT - pad + extrapad));

    return usedOffset;
}
