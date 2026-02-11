gsicc_find_zeroref_cache(gsicc_link_cache_t *icc_link_cache)
{
    gsicc_link_t *curr = NULL;


    curr = icc_link_cache->head;
    while (curr != NULL ) {
        if (curr->ref_count == 0) {
            curr->ref_count++;
            break;
        }
        curr = curr->next;
    }
    return(curr);
}
