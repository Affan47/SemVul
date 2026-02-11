checkSelfAssignment()
{
    if (!_settings->isEnabled("warning"))
        return;

    const Token *tok = findSelfAssignPattern(_tokenizer->tokens());
    while (tok) {
        if (Token::Match(tok->previous(), "[;{}.]") &&
            tok->varId() && tok->varId() == tok->tokAt(2)->varId() &&
            isTypeWithoutSideEffects(_tokenizer, tok->variable())) {
            bool err = true;


            if (Token::Match(tok->tokAt(-2), ") { %var% = %var% ; } else { %varid% =", tok->varId())) {

                const Token *tokif = tok->linkAt(-2)->previous();


                const Token *else_end = tok->linkAt(6);

                if (tokif && else_end && tokif->linenr() == else_end->linenr())
                    err = false;
            }

            if (err)
                selfAssignmentError(tok, tok->str());
        }

        tok = findSelfAssignPattern(tok->next());
    }
}
