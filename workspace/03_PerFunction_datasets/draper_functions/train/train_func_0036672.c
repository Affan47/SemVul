virtualDestructor()
{


    if (!_settings->inconclusive)
        return;

    createSymbolDatabase();

    std::list<SymbolDatabase::SpaceInfo *>::const_iterator i;

    for (i = symbolDatabase->spaceInfoList.begin(); i != symbolDatabase->spaceInfoList.end(); ++i)
    {
        const SymbolDatabase::SpaceInfo *info = *i;


        if (info->derivedFrom.empty())
            continue;


        const SymbolDatabase::Func *destructor = info->getDestructor();


        if (!destructor || !destructor->hasBody)
            continue;


        if (destructor->token->tokAt(3)->link() == destructor->token->tokAt(4))
            continue;

        const Token *derived = info->classDef;
        const Token *derivedClass = derived->tokAt(1);


        for (unsigned int j = 0; j < info->derivedFrom.size(); ++j)
        {

            if (info->derivedFrom[j].access == SymbolDatabase::Public && info->derivedFrom[j].spaceInfo)
            {
                const SymbolDatabase::SpaceInfo *spaceInfo = info->derivedFrom[j].spaceInfo;


                const std::string baseName = spaceInfo->className;


                const SymbolDatabase::Func *base_destructor = spaceInfo->getDestructor();
                const Token *base = 0;
                if (base_destructor)
                    base = base_destructor->token;


                if (!base_destructor)
                {
                    if (spaceInfo->derivedFrom.empty())
                        virtualDestructorError(spaceInfo->classDef, baseName, derivedClass->str());
                }
                else if (!base_destructor->isVirtual)
                {


                    if (spaceInfo->derivedFrom.empty())
                    {


                        if (base_destructor->access == SymbolDatabase::Public)
                            virtualDestructorError(base, baseName, derivedClass->str());
                    }
                }
            }
        }
    }
}
