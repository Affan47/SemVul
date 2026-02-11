simplifyBorland()
{
    for (Token *tok = _tokens; tok; tok = tok->next())
    {
        if (Token::Match(tok, "( __closure * %var% )"))
        {
            tok->deleteNext();
        }
    }


    for (Token *tok = _tokens; tok; tok = tok->next())
    {
        if (tok->str() == "{")
        {
            tok = tok->link();
            if (!tok)
                break;
        }

        if (Token::Match(tok, "class %var% :|{"))
        {
            unsigned int indentlevel = 0;
            for (Token *tok2 = tok; tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "{")
                {
                    if (indentlevel == 0)
                        indentlevel = 1;
                    else
                        tok2 = tok2->link();
                }
                else if (tok2->str() == "}")
                {
                    break;
                }
                else if (tok2->str() == "__property" &&
                         Token::Match(tok2->previous(), ";|{|}|protected:|public:|__published:"))
                {
                    while (tok2->next() && !Token::Match(tok2, "{|;"))
                        tok2->deleteThis();
                    if (Token::simpleMatch(tok2, "{"))
                    {
                        Token::eraseTokens(tok2, tok2->link());
                        tok2->deleteThis();
                        tok2->deleteThis();


                        tok2->previous()->insertToken(";");
                        tok2->previous()->insertToken("__property");
                        tok2->previous()->insertToken(";");
                    }
                }
            }
        }
    }
}
