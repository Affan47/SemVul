free_filter(usnic_if_filter_t *filter)
{
    int i;

    if (filter == NULL) {
        return;
    }

    if (NULL != filter->elts) {
        for (i = 0; i < filter->n_elt; ++i) {
            if (!filter->elts[i].is_netmask) {
                free(filter->elts[i].if_name);
            }
        }
        free(filter->elts);
    }
    free(filter);
}
