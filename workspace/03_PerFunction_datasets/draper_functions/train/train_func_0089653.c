postfixOperator()
{
    if (!_settings->isEnabled("performance"))
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();

    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            bool result = false;
            const Variable *var = tok->variable();
            if (var && Token::Match(tok, "%var% ++|--")) {
                if (Token::Match(tok->previous(), ";|{|}") && Token::Match(tok->tokAt(2), ";|,|)")) {
                    result = true;
                } else if (tok->strAt(-1) == ",") {
                    for (const Token* tok2 = tok->tokAt(2); tok2 != 0 && tok2->str() != ")"; tok2 = tok2->next()) {
                        if (tok2->str() == ";") {
                            result = true;
                            break;
                        } else if (tok2->str() == "(")
                            tok2 = tok2->link();
                    }
                } else if (tok->strAt(-1) == ".") {
                    for (const Token* tok2 = tok->tokAt(-2); tok2 != 0; tok2 = tok2->previous()) {
                        if (Token::Match(tok2, ";|{|}")) {
                            result = true;
                            break;
                        } else if (Token::Match(tok2, ")|]|>") && tok2->link())
                            tok2 = tok2->link();
                        else if (tok2->isAssignmentOp() || Token::Match(tok2, "(|["))
                            break;
                    }
                }
            }

            if (result) {
                if (var->isPointer() || var->isArray())
                    continue;

                const Token *decltok = var->nameToken();

                if (Token::Match(decltok->previous(), "iterator|const_iterator|reverse_iterator|const_reverse_iterator")) {

                    postfixOperatorError(tok);
                } else if (var->type()) {

                    postfixOperatorError(tok);
                }
            }
        }
    }
}
