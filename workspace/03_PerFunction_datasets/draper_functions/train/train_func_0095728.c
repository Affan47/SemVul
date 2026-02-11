l2n_16(u16 *num) {
    u16     tmp;

    if(!endian) return;

    tmp = *num;
    *num = ((tmp & 0xff00) >> 8) |
           ((tmp & 0x00ff) << 8);
}
