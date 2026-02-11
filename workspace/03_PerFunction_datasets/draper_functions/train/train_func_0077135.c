trie_fread (FILE *file)
{
    Trie       *trie;

    trie = (Trie *) malloc (sizeof (Trie));
    if (!trie)
        return NULL;

    if (NULL == (trie->alpha_map = alpha_map_fread_bin (file)))
        goto exit_trie_created;
    if (NULL == (trie->da   = da_fread (file)))
        goto exit_alpha_map_created;
    if (NULL == (trie->tail = tail_fread (file)))
        goto exit_da_created;

    trie->is_dirty = FALSE;
    return trie;

exit_da_created:
    da_free (trie->da);
exit_alpha_map_created:
    alpha_map_free (trie->alpha_map);
exit_trie_created:
    free (trie);
    return NULL;
}
