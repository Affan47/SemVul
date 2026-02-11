checkMemsetInvalid2ndParam()
{
    const bool portability = _settings->isEnabled("portability");
    const bool warning = _settings->isEnabled("warning");
    if (!warning && !portability)
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok && (tok != scope->classEnd); tok = tok->next()) {
            if (Token::simpleMatch(tok, "memset (")) {
                const Token* firstParamTok = tok->tokAt(2);
                if (!firstParamTok)
                    continue;
                const Token* secondParamTok = firstParamTok->nextArgument();
                if (!secondParamTok)
                    continue;


                if (Token::Match(secondParamTok, "%num% ,") && MathLib::isNullValue(secondParamTok->str()))
                    continue;

                const Token *top = secondParamTok;
                while (top->astParent() && top->astParent()->str() != ",")
                    top = top->astParent();


                if (portability && astIsFloat(top,false)) {
                    memsetFloatError(secondParamTok, top->expressionString());
                } else if (warning && secondParamTok->isNumber()) {
                    const long long int value = MathLib::toLongNumber(secondParamTok->str());
                    if (value < -128 || value > 255)
                        memsetValueOutOfRangeError(secondParamTok, secondParamTok->str());
                }
            }
        }
    }
}
