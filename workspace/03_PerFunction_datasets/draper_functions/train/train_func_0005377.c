make_div_dim_range(Array_range_semnode *dim_head,
                   const int dim,
                   const int stride_2nd_dim)
{
    Div_dim_range *ddr;
    int div_dim_num = dim - stride_2nd_dim;
    Array_range_semnode *r;
    int i;

    for (r = dim_head, i = 0;
         r != NULL && i < stride_2nd_dim;
         r = r->next_dim, i++);

    if (r == NULL || div_dim_num == 0) {
        return NULL;
    }

    ddr = zcalloc(1, sizeof(Div_dim_range));

    ddr->min = zcalloc(div_dim_num, sizeof(SemTree*));
    ddr->max = zcalloc(div_dim_num, sizeof(SemTree*));
    ddr->cnt = zcalloc(div_dim_num, sizeof(SemTree*));

    for (i = 0; r != NULL && i < div_dim_num; r = r->next_dim, i++) {
        ddr->min[i] = semtree_dup(r->lower_tree);
        ddr->max[i] = semtree_dup(r->upper_tree);
        ddr->cnt[i] = semtree_dup(r->lower_tree);
    }

    ddr->stride_2nd_dim = stride_2nd_dim;
    ddr->div_dim_num = div_dim_num;

    return ddr;
}
