validateScheme(const String& schemeName)
{
    OGRE_LOCK_AUTO_MUTEX;

    SGSchemeIterator itScheme = mSchemeEntriesMap.find(schemeName);


    if (itScheme == mSchemeEntriesMap.end())
        return false;

    itScheme->second->validate();

    return true;
}
