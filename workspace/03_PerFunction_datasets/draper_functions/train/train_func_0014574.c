stoi(struct json_token *tok)
{
    if (!tok->str || !tok->len)
        return 0;
    json_number n = 0;
    json_size i = 0;
    const json_size off = (tok->str[0] == '-' || tok->str[0] == '+') ? 1 : 0;
    const json_size neg = (tok->str[0] == '-') ? 1 : 0;
    for (i = off; i < tok->len; i++) {
        if ((tok->str[i] >= '0') && (tok->str[i] <= '9'))
            n = (n * 10) + tok->str[i]  - '0';
    }
    return (neg) ? -n : n;
}
