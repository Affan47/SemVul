destructors()
{
    const SymbolDatabase* const symbolDatabase = _tokenizer->getSymbolDatabase();


    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        const Function * j = scope->function;
        if (j) {

            if (j->type == Function::eDestructor) {

                for (const Token *tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {

                    if (Token::simpleMatch(tok, "try {")) {
                        tok = tok->next()->link();
                    }


                    if (tok->str() == "throw") {
                        destructorsError(tok);
                        break;
                    }
                }
            }
        }
    }
}
