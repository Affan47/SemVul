resetProfile1()
{
    register int sl;
    int i,j;
    int _gapPos1 = userParameters->getGapPos1();
    int _gapPos2 = userParameters->getGapPos2();
    bool _resetAlignNew = userParameters->getResetAlignmentsNew();
    bool _resetAlignAll = userParameters->getResetAlignmentsAll();

    if (userParameters->getStructPenalties1() != NONE)
    {
        sl = 0;
        for (j = 0; j < (int)gapPenaltyMask1.size(); ++j)
        {
            if (gapPenaltyMask1[j] == _gapPos1 && (_resetAlignNew ||
                           _resetAlignAll))
            {
                continue;
            }
            if (gapPenaltyMask1[j] == _gapPos2 && (_resetAlignAll))
            {
                continue;
            }
            gapPenaltyMask1[sl] = gapPenaltyMask1[j];
            ++sl;
        }
    }

    if (userParameters->getStructPenalties1() == SECST)
    {
        sl = 0;
        for (j = 0; j < (int)secStructMask1.size(); ++j)
        {
            if (secStructMask1[j] == _gapPos1 && (_resetAlignNew ||
                          _resetAlignAll))
            {
                continue;
            }
            if (secStructMask1[j] == _gapPos2 && (_resetAlignAll))
            {
                continue;
            }
            secStructMask1[sl] = secStructMask1[j];
            ++sl;
        }
    }

    for(i = 1; i <= profile1NumSeqs; ++i)
    {
        sl = 0;
        for(j = 1; j <= getSeqLength(i); ++j)
        {
            if(seqArray[i][j] == _gapPos1 && (_resetAlignNew || _resetAlignAll))
            {
                continue;
            }
            if(seqArray[i][j] == _gapPos2 && (_resetAlignAll))
            {
                continue;
            }
            ++sl;
            seqArray[i][sl] = seqArray[i][j];
        }


        int numExtraElements = seqArray[i].size() - 1 - sl;
        for(int k = 0; k < numExtraElements; k++)
        {
            seqArray[i].pop_back();
        }
    }
}
