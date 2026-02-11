qbase64_encode(const void *bin, size_t size) {
    const char B64CHARTBL[64] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
        'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
        'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'
    };

    if (size == 0) {
        return strdup("");
    }


    char *pszB64 = (char *) malloc(
            4 * ((size / 3) + ((size % 3 == 0) ? 0 : 1)) + 1);
    if (pszB64 == NULL) {
        return NULL;
    }

    char *pszB64Pt = pszB64;
    unsigned char *pBinPt, *pBinEnd = (unsigned char *) (bin + size - 1);
    unsigned char szIn[3] = { 0, 0, 0 };
    int nOffset;
    for (pBinPt = (unsigned char *) bin, nOffset = 0; pBinPt <= pBinEnd;
            pBinPt++, nOffset++) {
        int nIdxOfThree = nOffset % 3;
        szIn[nIdxOfThree] = *pBinPt;
        if (nIdxOfThree < 2 && pBinPt < pBinEnd)
            continue;

        *pszB64Pt++ = B64CHARTBL[((szIn[0] & 0xFC) >> 2)];
        *pszB64Pt++ = B64CHARTBL[(((szIn[0] & 0x03) << 4)
                | ((szIn[1] & 0xF0) >> 4))];
        *pszB64Pt++ =
                (nIdxOfThree >= 1) ?
                        B64CHARTBL[(((szIn[1] & 0x0F) << 2)
                                | ((szIn[2] & 0xC0) >> 6))] :
                        '=';
        *pszB64Pt++ = (nIdxOfThree >= 2) ? B64CHARTBL[(szIn[2] & 0x3F)] : '=';

        memset((void *) szIn, 0, sizeof(szIn));
    }
    *pszB64Pt = '\0';

    return pszB64;
}
