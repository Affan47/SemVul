cmd_put_frac31(register frac31 w, register byte * dp)
{
    register uint32_t v = w;

    while (v & 0x01FFFFFF)
        *dp++ = (v >> 24) | 1, v <<= 7;
    *dp = (v >> 24);
    return dp + 1;
}
