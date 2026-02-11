BearoffDist(const bearoffcontext * pbc, const unsigned int nPosID,
            float arProb[32], float arGammonProb[32],
            float ar[4], unsigned short int ausProb[32], unsigned short int ausGammonProb[32])
{
    g_return_val_if_fail(pbc, -1);
    g_return_val_if_fail(pbc->bt == BEAROFF_ONESIDED, -1);
    if (pbc->fND)
        return ReadBearoffOneSidedND(pbc, nPosID, arProb, arGammonProb, ar, ausProb, ausGammonProb);
    else
        return ReadBearoffOneSidedExact(pbc, nPosID, arProb, arGammonProb, ar, ausProb, ausGammonProb);
}
