checkSignConversion()
{
    if (!_settings->isEnabled("warning"))
        return;

    const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
    const std::size_t functions = symbolDatabase->functionScopes.size();
    for (std::size_t i = 0; i < functions; ++i) {
        const Scope * scope = symbolDatabase->functionScopes[i];
        for (const Token* tok = scope->classStart->next(); tok != scope->classEnd; tok = tok->next()) {
            if (!tok->isArithmeticalOp() || Token::Match(tok,"+|-"))
                continue;

            unsigned int size = 0;
            char sign = 0;
            if (!astGetSizeSign(_settings, tok, &size, &sign))
                continue;

            if (sign != 'u')
                continue;


            std::stack<const Token *> tokens;
            tokens.push(tok->astOperand1());
            tokens.push(tok->astOperand2());
            while (!tokens.empty()) {
                const Token *tok1 = tokens.top();
                tokens.pop();
                if (!tok1)
                    continue;
                if (tok1->str() == "(")
                    continue;
                const Variable *var = tok1->variable();
                if (var && tok1->getValueLE(-1,_settings)) {
                    bool signedvar = true;
                    for (const Token *type = var->typeStartToken();; type = type->next()) {
                        if (type->isUnsigned()) {
                            signedvar = false;
                            break;
                        }
                        if (type->isSigned())
                            break;
                        if (type->isName() && !Token::Match(type, "char|short|int|long|const")) {
                            signedvar = false;
                            break;
                        }
                        if (type == var->typeEndToken())
                            break;
                    }
                    if (signedvar) {
                        signConversionError(tok1);
                        break;
                    }
                }
            }
        }
    }
}
