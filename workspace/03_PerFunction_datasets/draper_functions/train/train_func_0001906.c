eliminate_consist_var_in_du_table(Array_def_use_table_semnode *table_head,
                                  int var_entry)
{
    Array_def_use_table_semnode *table;
    Array_region_list_semnode *region;
    Array_range_semnode *range;

    for(table = table_head;
        table != NULL;
        table = table->next)
    {
        for(region = table->region_head;
            region != NULL;
            region = region->next)
        {
            for(range = region->dim_head;
                range != NULL;
                range = range->next_dim)
            {
                if(range->upper_tree != NULL) {
                    if(semtree_has_scalar_entry(range->upper_tree, var_entry)) {
                        free_all_array_range_semnode(region->dim_head);
                        region->dim_head = NULL;
                        break;
                    }
                }
                if(range->lower_tree != NULL) {
                    if(semtree_has_scalar_entry(range->lower_tree, var_entry)) {
                        free_all_array_range_semnode(region->dim_head);
                        region->dim_head = NULL;
                        break;
                    }
                }
            }
        }
    }

    delete_null_region_list_semnode(table_head);
}
