md5_addn(fingerprint_ty *p, const void *vip, size_t inputLen)
{
    md5_ty         *context;
    unsigned int    i;
    unsigned int    idx;
    unsigned int    partLen;
    const unsigned char *input;

    input = vip;
    context = (md5_ty *)p;

    idx = (unsigned int)((context->count[0] >> 3) & 0x3F);

    if
    (
        (context->count[0] += ((unsigned long)inputLen << 3))
    <
        ((unsigned long)inputLen << 3)
    )
        context->count[1]++;
    context->count[1] += ((unsigned long)inputLen >> 29);
    partLen = 64 - idx;


    if (inputLen >= partLen)
    {
        memcpy(&context->buffer[idx], input, partLen);
        MD5Transform(context->state, context->buffer);
        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform(context->state, &input[i]);
        idx = 0;
    }
    else
        i = 0;

    memcpy(&context->buffer[idx], &input[i], inputLen - i);
}
