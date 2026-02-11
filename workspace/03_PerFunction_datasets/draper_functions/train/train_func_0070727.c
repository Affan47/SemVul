mit_crc32(krb5_pointer in, size_t in_length, unsigned long *cksum)
{
    register u_char *data;
    register u_long c = *cksum;
    register int idx;
    size_t i;

    data = (u_char *)in;
    for (i = 0; i < in_length; i++) {
        idx = (int) (data[i] ^ c);
        idx &= 0xff;
        c >>= 8;
        c ^= crc_table[idx];
    }

    *cksum = c;
}
