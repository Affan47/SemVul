osp(const unsigned int anBoard[25], const unsigned int nGames,
    unsigned int an[25], float arProbs[MAX_PROBS], float arGammonProbs[MAX_GAMMON_PROBS])
{

    int i, n;
    unsigned int nTotal, nOut;
    unsigned short int anProb[32];


    nTotal = nOut = 0;

    memcpy(an, anBoard, 25 * sizeof(int));

    for (i = 0; i < 25; ++i) {

        nTotal += anBoard[i];
        if (i > 5)
            nOut += anBoard[i];
    }


    if (nOut > 0)

        rollOSR(nGames, an, nOut, arProbs, MAX_PROBS, arGammonProbs, MAX_GAMMON_PROBS);
    else {


        for (i = 0; i < MAX_GAMMON_PROBS; ++i)
            arGammonProbs[i] = 0.0f;

        if (nTotal == 15)
            arGammonProbs[1] = 1.0f;
        else
            arGammonProbs[0] = 1.0f;


        for (i = 0; i < MAX_PROBS; ++i)
            arProbs[i] = 0.0f;

        getBearoffProbs(PositionBearoff(anBoard, pbc1->nPoints, pbc1->nChequers), anProb);

        for (i = 0; i < 32; ++i) {
            n = MIN(i, MAX_PROBS - 1);
            arProbs[n] += anProb[i] / 65535.0f;

        }

    }

    return nTotal;

}
