allocate_conflict_element(void)
{
    void *p;

    p = conflict_element_pool;
    if (p != NULL)
        conflict_element_pool = ((struct sr_conflict_element *) p) -> next;
    else
    {
        p = (void *) talloc(MAX(sizeof(struct sr_conflict_element),
                            sizeof(struct rr_conflict_element)));
        if (p == NULL)
            nospace(__FILE__, __LINE__);
    }

    return p;
}
