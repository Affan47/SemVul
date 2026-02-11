tiger_round(ulong64 *a, ulong64 *b, ulong64 *c, ulong64 x, int mul)
{
    ulong64 tmp;
    tmp = (*c ^= x);
           *a -= t1[byte(tmp, 0)] ^ t2[byte(tmp, 2)] ^ t3[byte(tmp, 4)] ^ t4[byte(tmp, 6)];
    tmp = (*b += t4[byte(tmp, 1)] ^ t3[byte(tmp, 3)] ^ t2[byte(tmp,5)] ^ t1[byte(tmp,7)]);
    switch (mul) {
        case 5:  *b = (tmp << 2) + tmp; break;
        case 7:  *b = (tmp << 3) - tmp; break;
        case 9:  *b = (tmp << 3) + tmp; break;
    }
}
