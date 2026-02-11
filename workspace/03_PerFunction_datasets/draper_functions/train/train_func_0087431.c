GenerateBearoff(unsigned char *p, unsigned int nId)
{
    unsigned int anRoll[2], anBoard[6], aProb[32];
    unsigned int i, iBest;
    unsigned short us;

    for (i = 0; i < 32; i++)
        aProb[i] = 0;

    for (anRoll[0] = 1; anRoll[0] <= 6; anRoll[0]++)
        for (anRoll[1] = 1; anRoll[1] <= anRoll[0]; anRoll[1]++) {
            PositionFromBearoff(anBoard, nId, HEURISTIC_P, HEURISTIC_C);
            iBest = HeuristicBearoff(anBoard, anRoll);

            g_assert(iBest < nId);

            if (anRoll[0] == anRoll[1])
                for (i = 0; i < 31; i++)
                    aProb[i + 1] += p[(iBest << 6) | (i << 1)] + (p[(iBest << 6) | (i << 1) | 1] << 8);
            else
                for (i = 0; i < 31; i++)
                    aProb[i + 1] += (p[(iBest << 6) | (i << 1)] +
                                     ((unsigned int) p[(iBest << 6) | (i << 1) | 1] << 8)) << 1;
        }

    for (i = 0; i < 32; i++) {
        us = (unsigned short) ((aProb[i] + 18) / 36);
        p[(nId << 6) | (i << 1)] = us & 0xFF;
        p[(nId << 6) | (i << 1) | 1] = us >> 8;
    }
}
