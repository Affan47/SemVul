transform()
{
    uint32_t *W = inBuf;
    uint32_t *H = hashBuf;


    for (int t = 16; t < 80 ; t++)
        W[t] = SHA_ROTL((W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]), 1);

    uint32_t a = H[0];
    uint32_t b = H[1];
    uint32_t c = H[2];
    uint32_t d = H[3];
    uint32_t e = H[4];

    uint32_t T;

    int t = 0;
    for ( ; t < 20 ; t++)
        {

        T = TR32(SHA_ROTL(a,5) + ((b&c)|((~b)&d)) +
                e + 0x5a827999L + W[t]);
        e = d; d = c; c = SHA_ROTL(b, 30); b = a; a = T;

        }
    for ( ; t < 40 ; t++)
        {
        T = TR32(SHA_ROTL(a,5) + (b^c^d) + e + 0x6ed9eba1L + W[t]);
        e = d; d = c; c = SHA_ROTL(b, 30); b = a; a = T;

        }
    for ( ; t < 60 ; t++)
        {
        T = TR32(SHA_ROTL(a,5) + ((b&c)^(b&d)^(c&d)) +
                e + 0x8f1bbcdcL + W[t]);
        e = d; d = c; c = SHA_ROTL(b, 30); b = a; a = T;

        }
    for ( ; t < 80 ; t++)
        {
        T = TR32(SHA_ROTL(a,5) + (b^c^d) +
                e + 0xca62c1d6L + W[t]);
        e = d; d = c; c = SHA_ROTL(b, 30); b = a; a = T;

        }

    H[0] = TR32(H[0] + a);
    H[1] = TR32(H[1] + b);
    H[2] = TR32(H[2] + c);
    H[3] = TR32(H[3] + d);
    H[4] = TR32(H[4] + e);
}
