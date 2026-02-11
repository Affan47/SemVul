transform()
{
    uint64_t *H = hashBuf;
    uint64_t *W = inBuf;


    for (int t = 16; t < 80 ; t++)
        W[t] = TR64(SHA_sigma1(W[t-2]) + W[t-7] + SHA_sigma0(W[t-15]) + W[t-16]);

    uint64_t a = H[0];
    uint64_t b = H[1];
    uint64_t c = H[2];
    uint64_t d = H[3];
    uint64_t e = H[4];
    uint64_t f = H[5];
    uint64_t g = H[6];
    uint64_t h = H[7];

    for (int t = 0 ; t < 80 ; t++)
        {

        uint64_t T1 = TR64(h + SHA_SIGMA1(e) + SHA_Ch(e,f,g) +
            sha512table[t] + W[t]);
        uint64_t T2 = TR64(SHA_SIGMA0(a) + SHA_Maj(a,b,c));
        h = g; g = f; f = e; e = TR64(d  + T1); d = c; c = b; b = a; a = TR64(T1 + T2);
        }

    H[0] = TR64(H[0] + a);
    H[1] = TR64(H[1] + b);
    H[2] = TR64(H[2] + c);
    H[3] = TR64(H[3] + d);
    H[4] = TR64(H[4] + e);
    H[5] = TR64(H[5] + f);
    H[6] = TR64(H[6] + g);
    H[7] = TR64(H[7] + h);
}
