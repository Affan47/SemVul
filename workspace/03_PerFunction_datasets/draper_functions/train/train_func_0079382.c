clarifyCalculation()
{
    if (!_settings->isEnabled("style"))
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            if (tok->str() == "?") {

                const Token *cond = tok->previous();
                if (cond->isName() || cond->isNumber())
                    cond = cond->previous();
                else if (cond->str() == ")")
                    cond = cond->link()->previous();
                else
                    continue;

                if (cond && cond->str() == "!")
                    cond = cond->previous();

                if (!cond)
                    continue;


                if (!cond->isArithmeticalOp())
                    continue;

                const std::string &op = cond->str();
                cond = cond->previous();


                while (cond && cond->previous()) {
                    if ((cond->isName() || cond->isNumber()) && cond->previous()->str() == "*")
                        cond = cond->tokAt(-2);
                    else if (cond->str() == ")")
                        cond = cond->link()->previous();
                    else
                        break;
                }

                if (!cond)
                    continue;


                if (cond->str() == ")") {
                    clarifyCalculationError(cond, op);
                } else if (cond->isName() || cond->isNumber()) {
                    if (Token::Match(cond->previous(),"return|=|+|-|,|(") || cond->strAt(-1) == op)
                        clarifyCalculationError(cond, op);
                }
            }
        }
    }
}
