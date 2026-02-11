simplifyErrNoInWhile()
{
    for (Token *tok = _tokens; tok; tok = tok->next())
    {
        if (tok->str() != "errno")
            continue;

        Token *endpar = 0;
        if (Token::Match(tok->previous(), "&& errno == EINTR ) { ;| }"))
            endpar = tok->tokAt(3);
        else if (Token::Match(tok->tokAt(-2), "&& ( errno == EINTR ) ) { ;| }"))
            endpar = tok->tokAt(4);
        else
            continue;

        if (Token::simpleMatch(endpar->link()->previous(), "while ("))
        {
            Token *tok1 = tok->previous();
            if (tok1->str() == "(")
                tok1 = tok1->previous();


            Token::eraseTokens(tok1->previous(), endpar);


            tok = endpar;

        }
    }
}
