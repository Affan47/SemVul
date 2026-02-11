finish()
{
    static const md5_byte_t pad[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    md5_byte_t data[8];
    int i;

    for (i = 0; i < 8; ++i)
        data[i] = (md5_byte_t)(count[i>>2] >> ((i&3)<<3));

    append(pad, ((55 - (count[0] >> 3)) & 63) + 1);

    append(data, 8);
    for (i = 0; i < 16; ++i)
        digest[i] = (md5_byte_t)(abcd[i>>2] >> ((i&3)<<3));
}
