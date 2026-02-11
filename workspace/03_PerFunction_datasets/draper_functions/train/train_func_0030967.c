warningOldStylePointerCast()
{
    if (!_settings->_checkCodingStyle ||
        (_tokenizer->tokens() && _tokenizer->fileLine(_tokenizer->tokens()).find(".cpp") == std::string::npos))
        return;

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {

        if (!Token::Match(tok, "( const| %type% * ) %var%") &&
            !Token::Match(tok, "( const| %type% * ) (| new"))
            continue;

        int addToIndex = 0;
        if (tok->tokAt(1)->str() == "const")
            addToIndex = 1;

        if (tok->tokAt(4 + addToIndex)->str() == "const")
            continue;


        const std::string pattern("class " + tok->tokAt(1 + addToIndex)->str());
        if (!Token::findmatch(_tokenizer->tokens(), pattern.c_str()))
            continue;

        cstyleCastError(tok);
    }
}
