check()
{
    SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();

    std::list<SymbolDatabase::SpaceInfo *>::iterator i;

    for (i = symbolDatabase->spaceInfoList.begin(); i != symbolDatabase->spaceInfoList.end(); ++i)
    {
        const SymbolDatabase::SpaceInfo *info = *i;


        if (info->type == SymbolDatabase::SpaceInfo::Class)
        {
            std::list<SymbolDatabase::Var>::const_iterator var;
            for (var = info->varlist.begin(); var != info->varlist.end(); ++var)
            {
                if (!var->isStatic && var->token->previous()->str() == "*")
                {

                    if (var->token->tokAt(-2)->isStandardType())
                    {
                        if (var->access == SymbolDatabase::Private)
                            checkPublicFunctions(info, var->token);

                        variable(info, var->token);
                    }


                    else if (var->type)
                    {

                        if (var->type->derivedFrom.empty() && var->type->numConstructors == 0)
                        {
                            if (var->access == SymbolDatabase::Private)
                                checkPublicFunctions(info, var->token);

                            variable(info, var->token);
                        }
                    }
                }
            }
        }
    }
}
