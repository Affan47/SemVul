double_block(block d, block s) {
    unsigned i;
    unsigned char tmp = s[0];
    for (i=0; i<15; i++)
        d[i] = (s[i] << 1) | (s[i+1] >> 7);
    d[15] = (s[15] << 1) ^ ((tmp >> 7) * 135);
}
