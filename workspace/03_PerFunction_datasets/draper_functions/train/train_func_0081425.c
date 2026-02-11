hash_count(HASH * table)
{
    int count, i;
    struct hash_elem *tmp;

    for (i = 0, count = 0; i < table->nelem; i++) {
        tmp = table->table[i];
        while(tmp) {
            tmp = tmp->next;
            count++;
        }
    }
    return count;
}
