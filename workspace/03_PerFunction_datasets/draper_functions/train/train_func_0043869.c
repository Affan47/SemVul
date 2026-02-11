tokenIsFunctionReturningBool(const Token* tok)
{
    const Function* func = tok->function();
    if (func && Token::Match(tok, "%var% (")) {
        if (func->tokenDef && func->tokenDef->strAt(-1) == "bool") {
            return true;
        }
    }
    return false;
}
