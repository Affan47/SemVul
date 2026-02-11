GetFileList(pnAuthFileItem* files, uint32_t infoSize,
                        const pl_wchar_t* infoBuffer)
{
    pnAuthFileItem* cur = files;
    while (((int)infoSize) > 0 && *infoBuffer != 0) {
        size_t fnLen = plwcslen(infoBuffer);
        cur->fFilename = plString(infoBuffer, fnLen);
        infoBuffer += fnLen + 1;
        infoSize -= fnLen + 1;

        cur->fFileSize = (infoBuffer[0] << 16) | (infoBuffer[1] & 0xFFFF);
        infoBuffer += 3;
        infoSize -= 3;
        cur++;
    }
}
