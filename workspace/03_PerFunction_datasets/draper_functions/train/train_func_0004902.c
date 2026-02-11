inList(StrList *sp, const char *s)
{
    for (; sp; sp = sp->next)
        if (!strcmp(sp->str, s))
            return True;
    return False;
}
