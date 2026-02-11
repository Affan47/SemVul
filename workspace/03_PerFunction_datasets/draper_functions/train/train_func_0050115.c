ReadBearoffOneSidedND(const bearoffcontext * pbc,
                      const unsigned int nPosID,
                      float arProb[32], float arGammonProb[32],
                      float *ar, unsigned short int ausProb[32], unsigned short int ausGammonProb[32])
{

    unsigned char ac[16];
    float arx[4];
    int i;
    float r;

    ReadBearoffFile(pbc, 40 + nPosID * 16, ac, 16);

    memcpy(arx, ac, 16);

    if (arProb || ausProb)
        for (i = 0; i < 32; ++i) {
            r = fnd(1.0f * i, arx[0], arx[1]);
            if (arProb)
                arProb[i] = r;
            if (ausProb)
                ausProb[i] = (unsigned short) (r * 65535.0f);
        }


    if (arGammonProb || ausGammonProb)
        for (i = 0; i < 32; ++i) {
            r = fnd(1.0f * i, arx[2], arx[3]);
            if (arGammonProb)
                arGammonProb[i] = r;
            if (ausGammonProb)
                ausGammonProb[i] = (unsigned short) (r * 65535.0f);
        }

    if (ar)
        memcpy(ar, arx, 16);

    ++((bearoffcontext *) pbc)->nReads;

    return 0;

}
