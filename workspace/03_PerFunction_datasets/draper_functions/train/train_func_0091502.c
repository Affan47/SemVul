checkModuloAlwaysTrueFalse()
{
    if (!_settings->isEnabled("warning"))
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            if ((Token::Match(tok, "% %num% %comp% %num%")) &&
                (!tok->tokAt(4) || !tok->tokAt(4)->isArithmeticalOp())) {
                if (MathLib::isLessEqual(tok->strAt(1), tok->strAt(3)))
                    moduloAlwaysTrueFalseError(tok, tok->strAt(1));
            }
        }
    }
}
