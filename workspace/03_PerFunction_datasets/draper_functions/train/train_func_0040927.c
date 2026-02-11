newStr(char *str)
{
    RcStr *cs;

    for (cs = strs; cs; cs = cs->next)
        if (!strcmp(str, cs->str)) {
            free(str);
            cs->cnt++;
            return cs;
        }
    if (!(cs = Malloc(sizeof(*cs))))
        return 0;
    cs->cnt = 1;
    cs->str = str;
    cs->next = strs;
    strs = cs;
    return cs;
}
