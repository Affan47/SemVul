checkAlwaysTrueOrFalseStringCompare()
{
    if (!_settings->isEnabled("style"))
        return;

    const char pattern1[] = "strncmp|strcmp|stricmp|strcmpi|strcasecmp|wcscmp ( %str% , %str% ";
    const char pattern2[] = "QString :: compare ( %str% , %str% )";
    const char pattern3[] = "strncmp|strcmp|stricmp|strcmpi|strcasecmp|wcscmp ( %var% , %var% ";

    const Token *tok = _tokenizer->tokens();
    while (tok && (tok = Token::findmatch(tok, pattern1)) != NULL) {
        const std::string &str1 = tok->strAt(2);
        const std::string &str2 = tok->strAt(4);
        alwaysTrueFalseStringCompareError(tok, str1, str2);
        tok = tok->tokAt(5);
    }

    tok = _tokenizer->tokens();
    while (tok && (tok = Token::findmatch(tok, pattern2)) != NULL) {
        const std::string &str1 = tok->strAt(4);
        const std::string &str2 = tok->strAt(6);
        alwaysTrueFalseStringCompareError(tok, str1, str2);
        tok = tok->tokAt(7);
    }

    tok = _tokenizer->tokens();
    while (tok && (tok = Token::findmatch(tok, pattern3)) != NULL) {
        const std::string &str1 = tok->strAt(2);
        const std::string &str2 = tok->strAt(4);
        if (str1 == str2)
            alwaysTrueStringVariableCompareError(tok, str1, str2);
        tok = tok->tokAt(5);
    }

    tok = _tokenizer->tokens();
    while (tok && (tok = Token::findmatch(tok, "!!+ %str% ==|!= %str% !!+")) != NULL) {
        const std::string &str1 = tok->strAt(1);
        const std::string &str2 = tok->strAt(3);
        alwaysTrueFalseStringCompareError(tok, str1, str2);
        tok = tok->tokAt(5);
    }
}
