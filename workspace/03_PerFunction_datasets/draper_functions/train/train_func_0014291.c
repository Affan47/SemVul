clarifyCondition()
{
    if (!_settings->isEnabled("style"))
        return;

    const bool isC = _tokenizer->isC();

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next()) {
        if (Token::Match(tok, "( %var% [=&|^]")) {
            for (const Token *tok2 = tok->tokAt(3); tok2; tok2 = tok2->next()) {
                if (tok2->str() == "(" || tok2->str() == "[")
                    tok2 = tok2->link();
                else if (tok2->type() == Token::eComparisonOp) {

                    if (!isC && tok2->link())
                        break;

                    clarifyConditionError(tok, tok->strAt(2) == "=", false);
                    break;
                } else if (!tok2->isName() && !tok2->isNumber() && tok2->str() != ".")
                    break;
            }
        }
    }


    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next()) {
        if (Token::Match(tok, "!|<|<=|==|!=|>|>=")) {
            if (tok->link())
                continue;

            const Token *tok2 = tok->next();


            if (Token::Match(tok2, "(|&"))
                continue;

            while (tok2 && (tok2->isName() || tok2->isNumber() || Token::Match(tok2,".|(|["))) {
                if (Token::Match(tok2, "(|["))
                    tok2 = tok2->link();
                tok2 = tok2->next();
            }

            if (Token::Match(tok2, "[&|^]")) {

                if (Token::Match(tok2, "&|* ,|>") || Token::simpleMatch(tok2->previous(), "const &"))
                    continue;


                if (!isC && Token::Match(tok->previous(), "%var% <")) {
                    const Token *tok3 = tok2;
                    while (Token::Match(tok3, "[&|^] %var%"))
                        tok3 = tok3->tokAt(2);
                    if (Token::Match(tok3, ",|>"))
                        continue;
                }

                clarifyConditionError(tok,false,true);
            }
        }
    }
}
