htbucket_insert(htbucket *b, void *key, void *data,
        int (*cmp)(const void*, const void*, const void*), const void *cmp_arg)
{
    struct htbucket_item *p, *ins;


    ins = malloc(sizeof *ins);
    if (!ins)
        return HT_ERROR;

    ins->key = key;
    ins->data = data;
    ins->next = NULL;


    if (!b->root)
    {
        b->root = ins;
        return HT_OK;
    }

    else if (cmp(key, b->root->key, cmp_arg) == 0)
    {
        free(ins);
        return HT_EXIST;
    }


    for (p = b->root; p->next; p = p->next)
    {
        if (cmp(key, p->next->key, cmp_arg) == 0)
        {
            free(ins);
            return HT_EXIST;
        }
    }

    p->next = ins;
    return HT_OK;
}
