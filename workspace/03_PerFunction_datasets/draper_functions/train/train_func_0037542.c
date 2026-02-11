blogc_split_list_variable(const char *name, b_trie_t *global, b_trie_t *local)
{
    const char *value = blogc_get_variable(name, global, local);
    if (value == NULL)
        return NULL;

    b_slist_t *rv = NULL;

    char **tmp = b_str_split(value, ' ', 0);
    for (unsigned int i = 0; tmp[i] != NULL; i++) {
        if (tmp[i][0] != '\0')
            rv = b_slist_append(rv, tmp[i]);
        else
            free(tmp[i]);
    }
    free(tmp);

    return rv;
}
