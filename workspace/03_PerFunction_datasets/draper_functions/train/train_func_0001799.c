tlfree(tl)

toplink *tl;
{
    toplink *nt = NULL;

    while (tl) {
        free(tl->description);
        free(tl->keyword);

        nt = tl->next;
        free(tl);
        tl = nt;
    }
    return;
}
