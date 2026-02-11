cf_tai64n_op_deserialize(void* data)
{
    char buffer[12];
    unsigned long long x;
    uint32 y;
    int i;

    deserialize_block_1(buffer, 8);

    x = 0ULL;
    for (i = 7; i >= 0; --i) {
        u_int8_t ch = (u_int8_t) buffer[i];
        x <<= 8;
        x |= (unsigned long long) ch;
    }

    y = 0UL;
    for (i = 11; i >= 8; --i) {
        u_int8_t ch = (u_int8_t) buffer[i];
        y <<= 8;
        y |= (unsigned long long) ch;
    }

    ((Cf_tai64n_t*) data)->s = x;
    ((Cf_tai64n_t*) data)->ns = y;
    return 12;
}
