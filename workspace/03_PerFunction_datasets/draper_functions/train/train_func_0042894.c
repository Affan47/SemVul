checkBoostForeachModification()
{
    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token *tok = scope->classStart->next(); tok && tok != scope->classEnd; tok = tok->next()) {
            if (!Token::simpleMatch(tok, "BOOST_FOREACH ("))
                continue;

            const Token *container_tok = tok->next()->link()->previous();
            if (!Token::Match(container_tok, "%var% ) {"))
                continue;

            const unsigned int container_id = container_tok->varId();
            if (container_id == 0)
                continue;

            const Token *tok2 = container_tok->tokAt(2);
            const Token *end = tok2->link();
            for (; tok2 != end; tok2 = tok2->next()) {
                if (Token::Match(tok2, "%varid% . insert|erase|push_back|push_front|pop_front|pop_back|clear|swap|resize|assign|merge|remove|remove_if|reverse|sort|splice|unique|pop|push", container_id)) {
                    boostForeachError(tok2);
                    break;
                }
            }
        }
    }
}
