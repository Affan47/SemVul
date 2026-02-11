rehash(struct hashtable *h, int s)
{
    int i,gs;
    struct hashentry *gt;

    gt=h->tab;
    gs=h->size;
    h->tab=CALLOC(s, struct hashentry);
    h->nent=h->nval;
    h->size=s;
    for(i=0;i<gs;i++)
    {
        if (gt[i].left && gt[i].left!=DELETED_HASHENTRY)
            add_hash_value(h, gt[i].left, gt[i].right);
    }
    CFREE(gt, gs, struct hashentry);
}
