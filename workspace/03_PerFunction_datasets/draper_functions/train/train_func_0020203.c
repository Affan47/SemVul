strstr_bmh(char *haystack, char *needle)
{
    int needleLen, haystackLen, bcTable[UCHAR_MAX + 1], i;

    needleLen = strlen(needle);
    haystackLen = strlen(haystack);


    if (needle[0] == '\0')
        return haystack;


    for (i = 0; i < UCHAR_MAX + 1; i++)
        bcTable[i] = needleLen;
    for (i = 0; i < needleLen - 1; i++)
        bcTable[(unsigned char)needle[i]] = needleLen - 1 - i;

    while (haystackLen >= needleLen){

        for (i = needleLen - 1; needle[i] == haystack[i]; i--)
            if (i == 0)
                return haystack;


        haystackLen -= bcTable[(unsigned char)haystack[needleLen - 1]];
        haystack += bcTable[(unsigned char)haystack[needleLen - 1]];
    }


    return NULL;
}
