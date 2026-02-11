invalidScanf()
{
    if (!_settings->_checkCodingStyle)
        return;
    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        const Token *formatToken = 0;
        if (Token::Match(tok, "scanf|vscanf ( %str% ,"))
            formatToken = tok->tokAt(2);
        else if (Token::Match(tok, "fscanf|vfscanf ( %var% , %str% ,"))
            formatToken = tok->tokAt(4);
        else
            continue;

        bool format = false;


        const std::string &formatstr(formatToken->str());
        for (unsigned int i = 1; i < formatstr.length(); i++)
        {
            if (formatstr[i] == '%')
                format = !format;

            else if (!format)
                continue;

            else if (std::isdigit(formatstr[i]))
            {
                format = false;
            }

            else if (std::isalpha(formatstr[i]))
            {
                invalidScanfError(tok);
                format = false;
            }
        }
    }
}
