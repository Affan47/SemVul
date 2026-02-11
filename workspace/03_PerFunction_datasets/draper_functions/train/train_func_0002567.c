namelist_append(t_namelist *listwas, const char *s, int allowdup)
{
    t_namelist *nl, *nl2;
    nl2 = (t_namelist *)(getbytes(sizeof(*nl)));
    nl2->nl_next = 0;
    nl2->nl_string = (char *)getbytes(strlen(s) + 1);
    strcpy(nl2->nl_string, s);
    sys_unbashfilename(nl2->nl_string, nl2->nl_string);
    if (!listwas)
        return (nl2);
    else
    {
        for (nl = listwas; ;)
        {
            if (!allowdup && !strcmp(nl->nl_string, s))
                return (listwas);
            if (!nl->nl_next)
                break;
            nl = nl->nl_next;
        }
        nl->nl_next = nl2;
    }
    return (listwas);
}
