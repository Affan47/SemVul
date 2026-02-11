show_hashlist(struct session *ses, struct hashtable *h, char *pat, const char *msg_all, const char *msg_none)
{
    struct listnode *templist;

    if (!*pat)
    {
        tintin_printf(ses, msg_all);
        templist=hash2list(h, "*");
    }
    else
        templist=hash2list(h, pat);
    show_list(templist);
    if (*pat && !templist->next)
        tintin_printf(ses, msg_none, pat);
    zap_list(templist);
    prompt(ses);
}
