unloadFactoryAliases()
{
    WindowFactoryManager& wfmgr = WindowFactoryManager::getSingleton();
    std::vector<AliasMapping>::iterator alias = d_aliasMappings.begin();


    for (;alias != d_aliasMappings.end(); ++alias)
    {

        WindowFactoryManager::TypeAliasIterator iter = wfmgr.getAliasIterator();


        while (!iter.isAtEnd() && (iter.getCurrentKey() != (*alias).aliasName))
            ++iter;


        if (!iter.isAtEnd())

            wfmgr.removeWindowTypeAlias((*alias).aliasName, (*alias).targetName);
    }
}
