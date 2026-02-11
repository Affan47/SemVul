valueFlowNumber(TokenList *tokenlist)
{
    for (Token *tok = tokenlist->front(); tok; tok = tok->next()) {
        if (tok->isNumber() && MathLib::isInt(tok->str()))
            setTokenValue(tok, ValueFlow::Value(MathLib::toLongNumber(tok->str())));
    }
}
