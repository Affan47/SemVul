OpenRow()
{
    mSolved = false;
    if (mColorPegs == NULL)
    {
        ;
    }
    else
    {
        for (int i = 0; i < mPegCnt; ++i)
        {
            if (mColorPegs[i] != NULL)
            {
                mColorPegs[i]->SetEnabled(true);
            }
        }
    }
    SetActive(true);
}
