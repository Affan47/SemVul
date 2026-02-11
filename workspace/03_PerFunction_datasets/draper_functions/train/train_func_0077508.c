new_hash_iter_context(hash_table_t *table)
{
    struct _hash_iter_context_t *iter;

    if (!table) return NULL;;

    iter = halloc(table, sizeof(struct _hash_iter_context_t));
    if (iter == NULL) {
        return NULL;
    }


    iter->iter.next = (hash_iter_next_t) hash_iter_next;

    iter->table = table;
    iter->i = 0;
    iter->j = 0;
    iter->s = table->directory[iter->i];
    iter->p = iter->s[iter->j];

    return (struct hash_iter_context_t *)iter;
}
