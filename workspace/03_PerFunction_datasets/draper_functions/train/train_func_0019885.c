hashtab_get(hashtab *ht, void *key)
{
    hashtab_slot *s;
    int i = ht->keyhsh(key) % ht->size;
    for (s = ht->slots[i]; s != NULL; s = s->next) {
        if (ht->keycmp(key, s->key)) {
            return s->data;
        }
    }
    return NULL;
}
