checkReturnPtrThis(const SymbolDatabase::SpaceInfo *info, const SymbolDatabase::Func *func, const Token *tok, const Token *last)
{
    bool foundReturn = false;

    for (; tok && tok != last; tok = tok->next())
    {

        if (tok->str() == "return")
        {
            foundReturn = true;
            std::string cast("( " + info->className + " & )");
            if (Token::Match(tok->next(), cast.c_str()))
                tok = tok->tokAt(4);


            if (Token::Match(tok->tokAt(1), "%any% (") &&
                tok->tokAt(2)->link()->next()->str() == ";")
            {
                std::list<SymbolDatabase::Func>::const_iterator it;


                for (it = info->functionList.begin(); it != info->functionList.end(); ++it)
                {

                    if (it->type == SymbolDatabase::Func::Function && it->hasBody &&
                        it->token->str() == tok->next()->str())
                    {

                        if (it->tokenDef->previous()->str() == "&" &&
                            it->tokenDef->strAt(-2) == info->className)
                        {

                            if (it->arg->link()->next()->str() != "const")
                                checkReturnPtrThis(info, &*it, it->arg->link()->next(), it->arg->link()->next()->link());
                        }
                    }
                }
            }


            else if (!(Token::Match(tok->tokAt(1), "(| * this ;|=") ||
                       Token::Match(tok->tokAt(1), "(| * this +=") ||
                       Token::Match(tok->tokAt(1), "operator = (")))
                operatorEqRetRefThisError(func->token);
        }
    }
    if (!foundReturn)
        operatorEqRetRefThisError(func->token);
}
