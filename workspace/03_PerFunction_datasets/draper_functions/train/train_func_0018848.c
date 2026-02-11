DroidDecipher(unsigned int* buf, unsigned int num) {
    unsigned int key = ((52 / num) + 6) * 0x9E3779B9;
    while (key != 0) {
        unsigned int xorkey = (key >> 2) & 3;
        unsigned int numloop = num - 1;
        while (numloop != 0) {
            buf[numloop] -=
              (((buf[numloop - 1] << 4) ^ (buf[numloop - 1] >> 3)) +
              ((buf[numloop - 1] >> 5) ^ (buf[numloop - 1] << 2))) ^
              ((fEKey[(numloop & 3) ^ xorkey] ^ buf[numloop - 1]) +
              (key ^ buf[numloop - 1]));
            numloop--;
        }
        buf[0] -=
          (((buf[num - 1] << 4) ^ (buf[num - 1] >> 3)) +
          ((buf[num - 1] >> 5) ^ (buf[num - 1] << 2))) ^
          ((fEKey[(numloop & 3) ^ xorkey] ^ buf[num - 1]) +
          (key ^ buf[num - 1]));
        key += 0x61C88647;
    }
}
