construct_non_align_range(Array_range_semnode *ars,
                          int align_dim,
                          int dim,
                          Module_table *module,
                          int entry)
{
    Non_align_range *new = NULL, *next_dim = NULL;

    if (dim != align_dim) {
        new = (Non_align_range *)calloc(1, sizeof(Non_align_range));
        if (new == NULL)
            fatal("alloc error.\n");

        new->dim = dim;
        new->range = make_non_align_range(ars);
        new->dim_size = calc_dim_size(new->range, module, entry, dim);
        new->next = NULL;
        if (ars->next_dim != NULL) {
            dim++;
            new->next_dim = construct_non_align_range(ars->next_dim,
                                                      align_dim,
                                                      dim,
                                                      module,
                                                      entry);
        }
    } else {
        if (ars->next_dim != NULL) {
            dim++;
            next_dim = construct_non_align_range(ars->next_dim,
                                                 align_dim,
                                                 dim,
                                                 module,
                                                 entry);
        }
    }

    if (new == NULL && next_dim == NULL)
        return NULL;
    else if (new == NULL && next_dim != NULL)
        return next_dim;

    return new;
}
