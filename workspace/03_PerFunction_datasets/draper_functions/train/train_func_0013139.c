printI64(char *buf,
         const U64 * pu64)
{
    U64             u64a;

    if (pu64->high & 0x80000000) {
        u64a.high = (uint32_t) ~pu64->high;
        u64a.low = (uint32_t) ~pu64->low;
        incrByU32(&u64a, 1);
        buf[0] = '-';
        printU64(buf + 1, &u64a);
    } else {
        printU64(buf, pu64);
    }
}
