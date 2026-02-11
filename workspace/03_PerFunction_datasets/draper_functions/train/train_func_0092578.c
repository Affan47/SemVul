sizeofsizeof()
{
    if (!_settings->_checkCodingStyle)
        return;
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::simpleMatch(tok, "sizeof sizeof"))
            sizeofsizeofError(tok);
    }
}
