checkSizeofForNumericParameter()
{
    if (!_settings->isEnabled("style"))
        return;

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next()) {
        if (Token::Match(tok, "sizeof ( %num% )")
            || Token::Match(tok, "sizeof %num%")
           ) {
            sizeofForNumericParameterError(tok);
        }
    }
}
