read_comment(tokenizer_t *tok)
{
    const wchar_t *start;

    start = tok->buff;
    while (*(tok->buff)!= L'\n' && *(tok->buff)!= L'\0')
        tok->buff++;


    size_t len = tok->buff - start;
    tok->last_token.assign(start, len);
    tok->last_type = TOK_COMMENT;
}
