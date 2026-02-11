simplifyDoWhileAddBracesHelper(Token *tok)
{
    if (Token::Match(tok->next(), "[),]"))
    {

        return false;
    }

    Token *tok1 = tok;
    Token *tok2 = NULL;
    Token *tok3 = tok->next();


    bool result = false;
    while (tok3)
    {
        if (tok3->str() == "{")
        {

            tok3 = tok3->link();
        }
        else if (tok3->str() == "while")
        {
            tok2 = tok3;
            break;
        }
        else if (Token::Match(tok3, "do {"))
        {

            tok3 = tok3->next()->link();
            if (Token::simpleMatch(tok3->next(), "while"))
                tok3 = tok3->next();
        }
        else if (Token::Match(tok3, "do !!{") &&
                 !Token::Match(tok3->next(), "[),]"))
        {


            tok1 = tok3;
            result = true;
        }

        tok3 = tok3->next();
    }

    if (tok2)
    {

        tok1->insertToken("{");


        tok2->previous()->insertToken("}");

        Token::createMutualLinks(tok1->next(), tok2->previous());
    }
    else
        result = false;

    return result;
}
