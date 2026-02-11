get_du_other_dim_size(Array_def_use_table_semnode *du,
                      Array_table *atbl,
                      const int target_dim)
{
    int i;
    SemTree *lower[MAX_DIM], *upper[MAX_DIM];
    int dim_size[MAX_DIM];
    int dim = atbl->dim;
    int tmp = 1;

    if (du == NULL) {
        return -1;
    }

    set_merged_one_array_du_semnode_size(du, atbl, lower, upper,
                                         dim_size);

    for (i = 0; i < dim; i++) {
        if (i != target_dim) {
            tmp *= dim_size[i];
        }
    }

    return tmp;
}
