IsInstalled()
{
    if (mInstalled == eUnknown)
    {
        mInstalled = IsPluginInstalled() ? eTrue : eFalse;
    }
    return mInstalled == eTrue;
}
