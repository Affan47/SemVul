SHA1Update(SHA1_CTX* context, const uint8* data, const size_t len)
{
    size_t i, j;
    uint32 int_len = (uint32)(len);

#ifdef VERBOSE
    SHAPrintContext(context, "before");
#endif

    j = (context->count[0] >> 3) & 63;
    if ((context->count[0] += int_len << 3) < (int_len << 3))
        context->count[1]++;

    context->count[1] += (int_len >> 29);
    if ((j + len) > 63) {
        memcpy(&context->buffer[j], data, (i = 64 - j));
        SHA1Transform(context->state, context->buffer);
        for ( ; i + 63 < len; i += 64) {
            SHA1Transform(context->state, data + i);
        }
        j = 0;
    }
    else i = 0;
    memcpy(&context->buffer[j], &data[i], len - i);

#ifdef VERBOSE
    SHAPrintContext(context, "after ");
#endif
}
