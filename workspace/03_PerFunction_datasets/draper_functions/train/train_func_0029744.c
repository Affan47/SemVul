RemovePeg(ColorPeg *cp)
{
    if (mColorPegs == NULL)
    {
        return;
    }

    for (int i = 0; i < mPegCnt; ++i)
    {
        if (mColorPegs[i] == cp)
        {
            mColorPegs[i] = NULL;
            if (mIsActive)
            {
                CheckSolution();
            }
        }
    }
}
