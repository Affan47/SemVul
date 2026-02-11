mprPopItem(MprList *lp)
{
    void    *item;
    int     index;

    item = NULL;
    if (lp->length > 0) {
        lock(lp);
        index = lp->length - 1;
        item = mprGetItem(lp, index);
        mprRemoveItemAtPos(lp, index);
        unlock(lp);
    }
    return item;
}
