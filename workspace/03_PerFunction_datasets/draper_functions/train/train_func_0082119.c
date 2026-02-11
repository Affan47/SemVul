getSourceModifier(unsigned short index, SourceModifier& modType, int& customNum) const
{
    modType = SM_Invalid;
    customNum = 0;
    if(index < mTextureBlends.size())
    {
        modType = mTextureBlends[index].sourceModifier;
        customNum = mTextureBlends[index].customNum;
    }
    return (modType != SM_Invalid);
}
