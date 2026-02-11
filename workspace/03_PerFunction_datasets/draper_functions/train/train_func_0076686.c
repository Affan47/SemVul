GetSequence(const byte* input, word32* inOutIdx, int* len)
{
    int    length = -1;
    word32 idx    = *inOutIdx;

    if (input[idx++] != (ASN_SEQUENCE | ASN_CONSTRUCTED) ||
            GetLength(input, &idx, &length) < 0)
        return ASN_PARSE_E;

    *len      = length;
    *inOutIdx = idx;

    return length;
}
