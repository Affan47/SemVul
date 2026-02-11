RestartGame()
{
    if (mGuessCnt > 0)
    {
        ++mRestartCnt;
    }

    for (int i = 0 ; i < mMaxGuessCnt ; ++i)
    {
        mHist[i] = NULL;
    }

    mGuessCnt = 0;
}
