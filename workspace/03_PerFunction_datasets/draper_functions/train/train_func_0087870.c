is_symbol(char sym)
{
    static char syms[] = { '=', '{', '}', ';', '\'', '"', ',', '/', '\\' };
    unsigned int i;

    for (i = 0; i < sizeof(syms) / sizeof(char); i++)
    {
        if (sym == syms[i])
            return 1;
    }

    return 0;
}
