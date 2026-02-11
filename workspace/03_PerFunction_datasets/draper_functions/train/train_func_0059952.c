get_utf8(GetBitContext *gb)
{
    int64_t val;
    GET_UTF8(val, get_bits(gb, 8), return -1;)
    return val;
}
