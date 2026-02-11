findmatch(const Token *tok1, const Token *tok2, const char pattern[])
{
    for (const Token *tok = tok1; tok && tok != tok2; tok = tok->next())
    {
        if (Token::Match(tok, pattern))
            return true;
    }
    return false;
}
