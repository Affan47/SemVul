hasAssignSelf(const Token *first, const Token *last, const Token *rhs)
{
    for (const Token *tok = first; tok && tok != last; tok = tok->next())
    {
        if (Token::Match(tok, "if ("))
        {
            const Token *tok1 = tok->tokAt(2);
            const Token *tok2 = tok->tokAt(1)->link();

            if (tok1 && tok2)
            {
                for (; tok1 && tok1 != tok2; tok1 = tok1->next())
                {
                    if (Token::Match(tok1, "this ==|!= & %var%"))
                    {
                        if (tok1->tokAt(3)->str() == rhs->str())
                            return true;
                    }
                    else if (Token::Match(tok1, "& %var% ==|!= this"))
                    {
                        if (tok1->tokAt(1)->str() == rhs->str())
                            return true;
                    }
                }
            }
        }
    }

    return false;
}
