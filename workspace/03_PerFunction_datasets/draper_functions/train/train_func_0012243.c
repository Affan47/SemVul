get_word(char *str, char **word)
{
    char *p = str;
    char *q;

    while (*p && !my_isspace(*p))
	p++;

    *word = q = refstr_alloc(p - str);
    memcpy(q, str, p - str);


    return p;
}
