change_dtu_trans_group_var_entry(Dtu_entry_table *ept, const int entry,
				 Var_table *ltbl)
{
    Array_range_semnode *range;

    for (range = ept->srange; range != NULL; range = range->next_dim) {
        if (range->lower_tree != NULL
            && semtree_has_scalar_entry(range->lower_tree, entry)) {
            replace_scalar_entry_to_semtree(range->lower_tree, entry,
                                            ltbl->entry, KIND_VAR);
        }
        if (range->upper_tree != NULL
            && semtree_has_scalar_entry(range->upper_tree, entry)) {
            replace_scalar_entry_to_semtree(range->upper_tree, entry,
                                            ltbl->entry, KIND_VAR);
        }
    }
    for (range = ept->drange; range != NULL; range = range->next_dim) {
        if (range->lower_tree != NULL
            && semtree_has_scalar_entry(range->lower_tree, entry)) {
            replace_scalar_entry_to_semtree(range->lower_tree, entry,
                                            ltbl->entry, KIND_VAR);
        }
        if (range->upper_tree != NULL
            && semtree_has_scalar_entry(range->upper_tree, entry)) {
            replace_scalar_entry_to_semtree(range->upper_tree, entry,
                                            ltbl->entry, KIND_VAR);
        }
    }
}
