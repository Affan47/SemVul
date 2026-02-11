replace_arg_var_array_range_semnode(Array_range_semnode *range_head,
                                    SemTree **arg_var_tbl,
                                    int vmax)
{
    Array_range_semnode *rpt;
    int i;

    for (rpt = range_head; rpt != NULL; rpt = rpt->next_dim) {
        for (i = 0; i < vmax + 1; i++) {
            if (arg_var_tbl[i] != NULL) {
                if (rpt->lower_tree != NULL) {
                    semtree_replace_scalar(rpt->lower_tree,
                                           i,
                                           semtree_dup(arg_var_tbl[i]));
                }
                if (rpt->upper_tree != NULL) {
                    semtree_replace_scalar(rpt->upper_tree,
                                           i,
                                           semtree_dup(arg_var_tbl[i]));
                }
                if (rpt->step_tree != NULL) {
                    semtree_replace_scalar(rpt->step_tree,
                                           i,
                                           semtree_dup(arg_var_tbl[i]));
                }
            }
        }
    }
}
