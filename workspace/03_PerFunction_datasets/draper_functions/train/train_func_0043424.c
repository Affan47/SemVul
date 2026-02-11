cx_bits_rfind(cxuint32 mask, cxint start)
{

    register cxint n = (cxint)(sizeof(cxuint32) * 8);

    if (start < 0)
        start = -1;

    while (start < n) {
        start++;
        if (mask & (1 << (cxuint32)start))
            return start;
    }

    return -1;
}
