QuasiRandomSeed(perArray * pArray, int n)
{

    int i, j, r;
    unsigned char k, t;
    randctx rc;

    if (pArray->nPermutationSeed == n)
        return;

    for (i = 0; i < RANDSIZ; i++)
        rc.randrsl[i] = (unsigned long) n;

    irandinit(&rc, TRUE);

    for (i = 0; i < 6; i++)
        for (j = i  ; j < 128; j++) {
            for (k = 0; k < 36; k++)
                pArray->aaanPermutation[i][j][k] = k;
            for (k = 0; k < 35; k++) {
                r = irand(&rc) % (36 - k);
                t = pArray->aaanPermutation[i][j][k + r];
                pArray->aaanPermutation[i][j][k + r] = pArray->aaanPermutation[i][j][k];
                pArray->aaanPermutation[i][j][k] = t;
            }
        }

    pArray->nPermutationSeed = n;
}
