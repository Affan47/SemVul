RandRowSlot()
{
    if (mCurRow == NULL || !mCurRow->IsActive() || mGameState != STATE_RUNNING)
    {
        return;
    }

    if (mGameMode == MODE_HVM || (mGameMode == MODE_MVH && mCurRow == mSolutionRow))
    {
        mCurRow->ClearRow();

        int i, rndm;
        int check[mColorCnt];
        ColorPeg* peg;
        for (i = 0; i < mColorCnt; ++i)
        {
            check[i] = 0;
        }

        for (i = 0; i < mPegCnt; ++i)
        {
            rndm = qrand() % mColorCnt;
            if (mDoubles == 0 && check[rndm] != 0)
            {
                --i;
                continue;
            }

            check[rndm] = 1;

            peg = mPegFactory->CreatePeg(rndm);
            mCurRow->ForceSnap(peg, i);
        }
    }
}
