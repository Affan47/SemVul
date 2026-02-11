user_copyquotaroot(char *oldname, char *newname)
{
    int r = 0;
    struct quota q;

    q.root = oldname;
    r = quota_read(&q, NULL, 0);
    if (!r) mboxlist_setquota(newname, q.limit, 0);

    return r;
}
