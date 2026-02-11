getHerculesStderr()
{
    if (mStderr == NULL)
    {
        mStderr = fopen(mFifo2.c_str(),"w");
    }
    return mStderr;
}
