assignFunctionArg()
{
    if (!_settings->isEnabled("warning"))
        return;
    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token *tok = scope->classStart; tok && tok != scope->classEnd; tok = tok->next()) {
            if (Token::Match(tok, "[;{}] %var% =") &&
                isNonReferenceArg(tok->next()) &&
                !variableIsUsedInScope(Token::findsimplematch(tok->tokAt(2), ";"), tok->next()->varId(), scope)) {
                errorUselessAssignmentPtrArg(tok->next());
            }
        }
    }
}
