dio_ReadULEB128(void) {
    U4_T Res = 0;
    int i = 0;
    for (;; i += 7) {
        U1_T n = dio_ReadU1();
        Res |= (n & 0x7Fu) << i;
        if ((n & 0x80) == 0) break;
    }
    return Res;
}
