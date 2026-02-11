deallocThrow()
{


    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {

        if (tok->str() != "delete")
            continue;


        tok = tok->next();
        if (Token::simpleMatch(tok, "[ ]"))
            tok = tok->tokAt(2);
        if (!tok)
            break;
        if (!Token::Match(tok, "%var% ;"))
            continue;
        const unsigned int varid(tok->varId());
        if (varid == 0)
            continue;


        {

            bool globalVar = false;
            for (const Token *tok2 = _tokenizer->tokens(); tok2; tok2 = tok2->next())
            {
                if (tok->varId() == varid)
                {
                    globalVar = true;
                    break;
                }

                if (tok2->str() == "class")
                {
                    while (tok2 && tok2->str() != ";" && tok2->str() != "{")
                        tok2 = tok2->next();
                    tok2 = tok2 ? tok2->next() : 0;
                    if (!tok2)
                        break;
                }

                if (tok2->str() == "{")
                {
                    tok2 = tok2->link();
                    if (!tok2)
                        break;
                }
            }


            if (!globalVar)
                continue;
        }


        unsigned int indentlevel = 0;


        const Token *ThrowToken = 0;


        for (const Token *tok2 = tok; tok2; tok2 = tok2->next())
        {
            if (tok2->str() == "{")
                ++indentlevel;
            else if (tok2->str() == "}")
            {
                if (indentlevel == 0)
                    break;
                --indentlevel;
            }

            if (tok2->str() == "throw")
                ThrowToken = tok2;


            else if (Token::Match(tok2, "%varid% =", varid))
            {
                if (ThrowToken)
                    deallocThrowError(ThrowToken, tok->str());
                break;
            }
        }
    }
}
