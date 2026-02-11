createNormalizedAliasStrings(char *normalizedStrings, const char *origStringBlock, int32_t stringBlockLength) {
    int32_t currStrLen;
    uprv_memcpy(normalizedStrings, origStringBlock, stringBlockLength);
    while ((currStrLen = (int32_t)uprv_strlen(origStringBlock)) < stringBlockLength) {
        int32_t currStrSize = currStrLen + 1;
        if (currStrLen > 0) {
            int32_t normStrLen;
            ucnv_io_stripForCompare(normalizedStrings, origStringBlock);
            normStrLen = uprv_strlen(normalizedStrings);
            if (normStrLen > 0) {
                uprv_memset(normalizedStrings + normStrLen, 0, currStrSize - normStrLen);
            }
        }
        stringBlockLength -= currStrSize;
        normalizedStrings += currStrSize;
        origStringBlock += currStrSize;
    }
}
