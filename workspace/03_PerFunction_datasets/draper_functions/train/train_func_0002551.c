getHerculesCommandsFile()
{
    if (mStdinOutput == NULL)
    {
        if (mStdinOutput == NULL)
            mStdinOutput = fopen(mFifo0.c_str(),"w");
    }
    return mStdinOutput;
}
