EXPmatch(char *p, NEWSGROUP *v, char mod)
{
    NEWSGROUP           *ngp;
    int                 i;
    bool                negate;

    negate = *p == '!';
    if (negate)
        p++;
    for (ngp = Groups, i = nGroups; --i >= 0; ngp++)
        if (negate ? !uwildmat(ngp->Name, p) : uwildmat(ngp->Name, p))
            if (mod == 'a'
             || (mod == 'm' && ngp->Rest[0] == NF_FLAG_MODERATED)
             || (mod == 'u' && ngp->Rest[0] != NF_FLAG_MODERATED)) {
                ngp->Keep      = v->Keep;
                ngp->Default   = v->Default;
                ngp->Purge     = v->Purge;
                ngp->Poison    = v->Poison;
            }
}
