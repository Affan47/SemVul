utf8_length(const unsigned char *start, const unsigned char *end)
{
    unsigned char mask = 0x80;
    const unsigned char *p;
    int length = 0;
    int left;

    for (; mask > 0 && (*start & mask) == mask; mask >>= 1)
        length++;
    if (length < 2 || length > 6)
        return 1;
    if (end != NULL && (end - start + 1) < length)
        return 1;
    left = length - 1;
    for (p = start + 1; left > 0 && (*p & 0xc0) == 0x80; p++)
        left--;
    return (left == 0) ? length : 1;
}
