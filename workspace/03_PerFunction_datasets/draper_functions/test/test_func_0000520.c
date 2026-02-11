simplifyTemplatesGetTemplateInstantiations(Token *tokens)
{
    std::list<Token *> used;

    for (Token *tok = tokens; tok; tok = tok->next()) {

        if (Token::simpleMatch(tok, "template <")) {
            tok->next()->findClosingBracket(tok);
            if (!tok)
                break;
        } else if (Token::Match(tok->previous(), "[({};=] %var% <") ||
                   Token::Match(tok->tokAt(-2), "[,:] private|protected|public %var% <")) {


            const Token *tok2;
            tok->next()->findClosingBracket(tok2);


            for (; tok2 && tok2 != tok; tok2 = tok2->previous()) {
                if (Token::Match(tok2, ", %var% <") &&
                    TemplateSimplifier::templateParameters(tok2->tokAt(2))) {
                    used.push_back(tok2->next());
                }
            }


            if (TemplateSimplifier::templateParameters(tok->next()))
                used.push_back(tok);
        }
    }

    return used;
}
