ht_init(size_t size, int (*hash_func) (void *, size_t, size_t))
{
    hashtab_t *new_ht = (hashtab_t *) malloc(sizeof(hashtab_t));

    new_ht->arr =
	(hashtab_node_t **) malloc(sizeof(hashtab_node_t *) * size);

    new_ht->size = size;
    new_ht->count = 0;


    int i = 0;
    for (i = 0; i < (int) size; i++) {
	new_ht->arr[i] = NULL;
    }

    if (hash_func == NULL)
	new_ht->hash_func = &ht_hash;
    else
	new_ht->hash_func = hash_func;

    return new_ht;
}
