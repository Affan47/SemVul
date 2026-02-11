delStr(RcStr *str)
{
    RcStr **cs;

    if (!str || --str->cnt)
        return;
    for (cs = &strs; *cs; cs = &((*cs)->next))
        if (str == *cs) {
            *cs = (*cs)->next;
            free((*cs)->str);
            free(*cs);
            break;
        }
}
