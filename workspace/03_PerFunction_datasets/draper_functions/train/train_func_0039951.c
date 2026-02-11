GetExplicitVersion(const byte* input, word32* inOutIdx, int* version)
{
    word32 idx = *inOutIdx;

    if (input[idx++] == (ASN_CONTEXT_SPECIFIC | ASN_CONSTRUCTED)) {
        *inOutIdx = ++idx;
        return GetMyVersion(input, inOutIdx, version);
    }


    *version = 0;

    return 0;
}
