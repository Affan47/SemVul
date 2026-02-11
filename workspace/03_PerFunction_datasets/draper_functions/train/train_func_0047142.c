strPlusChar()
{
    const SymbolDatabase* symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            if (tok->str() == "+") {
                if (tok->astOperand1() && (tok->astOperand1()->type() == Token::eString)) {
                    if (tok->astOperand2() && (tok->astOperand2()->type() == Token::eChar || isChar(tok->astOperand2()->variable())))
                        strPlusCharError(tok);
                }
            }
        }
    }
}
