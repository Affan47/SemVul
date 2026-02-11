json_cmp(struct json_token* tok, const json_char* str)
{
    if (!tok || !str)
        return 1;

    json_size i;
    for (i = 0; (i < tok->len && *str); i++, str++){
        if (tok->str[i] != *str)
            return 1;
    }
    return 0;
}
