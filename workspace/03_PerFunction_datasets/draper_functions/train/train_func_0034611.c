hashtable_insert(struct hashtable *h, void *k, void *v)
{

    unsigned int index;
    struct entry *e;
    if (++(h->entrycount) > h->loadlimit)
    {


        hashtable_expand(h);
    }
    e = (struct entry *)malloc(sizeof(struct entry));
    if (NULL == e) { --(h->entrycount); return 0; }
    e->h = hash(h,k);
    index = indexFor(h->tablelength,e->h);
    e->k = k;
    e->v = v;
    e->next = h->table[index];
    h->table[index] = e;
    return -1;
}
