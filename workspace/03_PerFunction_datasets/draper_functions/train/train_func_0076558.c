destroyProgramSet()
{
    if (mProgramSet != NULL)
    {
        OGRE_DELETE mProgramSet;
        mProgramSet = NULL;
    }
}
