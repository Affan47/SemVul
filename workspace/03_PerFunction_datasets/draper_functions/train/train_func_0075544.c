ThorpCount(const TanBoard anBoard, int *pnLeader, float *adjusted, int *pnTrailer)
{

    int anCovered[2], anMenLeft[2];
    int x;
    unsigned int anPips[2];

    PipCount(anBoard, anPips);

    anMenLeft[0] = 0;
    anMenLeft[1] = 0;
    for (x = 0; x < 25; x++) {
        anMenLeft[0] += anBoard[0][x];
        anMenLeft[1] += anBoard[1][x];
    }

    anCovered[0] = 0;
    anCovered[1] = 0;
    for (x = 0; x < 6; x++) {
        if (anBoard[0][x])
            anCovered[0]++;
        if (anBoard[1][x])
            anCovered[1]++;
    }

    *pnLeader = anPips[1];
    *pnLeader += 2 * anMenLeft[1];
    *pnLeader += anBoard[1][0];
    *pnLeader -= anCovered[1];
    if (*pnLeader > 30)
        *adjusted = (float) (*pnLeader * 1.1f);
    else
        *adjusted = (float) *pnLeader;

    *pnTrailer = anPips[0];
    *pnTrailer += 2 * anMenLeft[0];
    *pnTrailer += anBoard[0][0];
    *pnTrailer -= anCovered[0];

    return 0;

}
