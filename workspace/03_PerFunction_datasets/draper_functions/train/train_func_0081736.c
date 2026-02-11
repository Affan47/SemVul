erase()
{
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::simpleMatch(tok, "for ("))
        {
            for (const Token *tok2 = tok->tokAt(2); tok2; tok2 = tok2->next())
            {
                if (tok2->str() == ";")
                {
                    if (Token::Match(tok2, "; %var% !="))
                    {
                        const unsigned int varid = tok2->next()->varId();
                        if (varid > 0 && Token::findmatch(_tokenizer->tokens(), "> :: iterator %varid%", varid))
                            EraseCheckLoop::checkScope(this, tok2->next());
                    }
                    break;
                }

                if (Token::Match(tok2, "%var% = %var% . begin ( ) ; %var% != %var% . end ( ) ") &&
                    tok2->str() == tok2->tokAt(8)->str() &&
                    tok2->tokAt(2)->str() == tok2->tokAt(10)->str())
                {
                    EraseCheckLoop::checkScope(this, tok2);
                    break;
                }
            }
        }

        if (Token::Match(tok, "while ( %var% !="))
        {
            const unsigned int varid = tok->tokAt(2)->varId();
            if (varid > 0 && Token::findmatch(_tokenizer->tokens(), "> :: iterator %varid%", varid))
                EraseCheckLoop::checkScope(this, tok->tokAt(2));
        }
    }
}
