ht_statistics(hashtable *ht, int *n_items, int *n_buckets, int *empty, int *one, int *gtone, int *max, double *avg)
{
    int i;
    size_t n;
    struct htbucket_item *bi;

    *empty = *one = *gtone = *max = 0;
    *n_items = ht->n_items;
    *n_buckets = ht->n_buckets;

    for (i=0; i<ht->n_buckets; i++)
    {
        n = 0;
        for (bi = ht->buckets[i].root; bi; bi = bi->next)
            n++;

        switch (n) {
            case 0:
                (*empty)++;
                break;
            case 1:
                (*one)++;
                break;
            default:
                (*gtone)++;
                break;
        }
        if (n > *max)
            *max = n;
    }

    *avg = (double)ht->n_items / (ht->n_buckets - *empty);
}
