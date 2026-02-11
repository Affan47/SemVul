Psi(ICESTATE SS, ICESTATE S)
{
    unsigned int x;
    for (x = 0; x < 4; ++x) {
        uint64_t tmp1 = S[x][0] & S[x][1] & S[x][2] & S[x][3] & S[x][4];
        uint64_t tmp2 = (~S[x][0]) & (~S[x][1]) & (~S[x][2]) & (~S[x][3]) & (~S[x][4]);
        SS[x][0] = S[x][0] ^ ((~S[x][1]) & S[x][2]) ^ tmp1 ^ tmp2;
        SS[x][1] = S[x][1] ^ ((~S[x][2]) & S[x][3]) ^ tmp1 ^ tmp2;
        SS[x][2] = S[x][2] ^ ((~S[x][3]) & S[x][4]) ^ tmp1 ^ tmp2;
        SS[x][3] = S[x][3] ^ ((~S[x][4]) & S[x][0]) ^ tmp1 ^ tmp2;
        SS[x][4] = S[x][4] ^ ((~S[x][0]) & S[x][1]) ^ tmp1 ^ tmp2;
    }
}
