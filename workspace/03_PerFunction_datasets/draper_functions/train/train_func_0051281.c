build_xlaw_table(uint8_t *linear_to_xlaw,
                             int (*xlaw2linear)(unsigned char),
                             int mask)
{
    int i, j, v, v1, v2;

    j = 0;
    for(i=0;i<128;i++) {
        if (i != 127) {
            v1 = xlaw2linear(i ^ mask);
            v2 = xlaw2linear((i + 1) ^ mask);
            v = (v1 + v2 + 4) >> 3;
        } else {
            v = 8192;
        }
        for(;j<v;j++) {
            linear_to_xlaw[8192 + j] = (i ^ mask);
            if (j > 0)
                linear_to_xlaw[8192 - j] = (i ^ (mask ^ 0x80));
        }
    }
    linear_to_xlaw[0] = linear_to_xlaw[1];
}
