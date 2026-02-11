sb_trie_insert(sb_trie_t *trie, const char *key, void *data)
{
    if (trie == NULL || key == NULL || data == NULL)
        return;

    sb_trie_node_t *parent = NULL;
    sb_trie_node_t *previous;
    sb_trie_node_t *current;
    sb_trie_node_t *tmp;

    while (1) {

        if (trie->root == NULL || (parent != NULL && parent->child == NULL)) {
            current = sb_malloc(sizeof(sb_trie_node_t));
            current->key = *key;
            current->data = NULL;
            current->next = NULL;
            current->child = NULL;
            if (trie->root == NULL)
                trie->root = current;
            else
                parent->child = current;
            parent = current;
            goto clean;
        }

        tmp = parent == NULL ? trie->root : parent->child;
        previous = NULL;

        while (tmp != NULL && tmp->key != *key) {
            previous = tmp;
            tmp = tmp->next;
        }

        parent = tmp;

        if (previous == NULL || parent != NULL)
            goto clean;

        current = sb_malloc(sizeof(sb_trie_node_t));
        current->key = *key;
        current->data = NULL;
        current->next = NULL;
        current->child = NULL;
        previous->next = current;
        parent = current;

clean:
        if (*key == '\0') {
            if (parent->data != NULL && trie->free_func != NULL)
                trie->free_func(parent->data);
            parent->data = data;
            break;
        }
        key++;
    }
}
