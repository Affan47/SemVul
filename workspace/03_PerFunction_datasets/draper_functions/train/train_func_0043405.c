cmd_put_w(register uint w, register byte * dp)
{
    while (w > 0x7f)
        *dp++ = w | 0x80, w >>= 7;
    *dp = w;
    return dp + 1;
}
