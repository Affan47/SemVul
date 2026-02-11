calc_dt_block_list(List *blklist,
                   IntSet local_array,
                   Array_def_use_table_semnode *(*get_block_dt)())
{
    Module_table *module;
    List *li;
    Array_def_use_table_semnode *dt = NULL, *tmp;

    if (blklist == NULL) return NULL;

    module = ((Block*)(blklist->data))->module;

    for (li = blklist; li != NULL; li = li->next) {
        Block *bpt = li->data;
        tmp = get_block_dt(bpt, local_array);
        dt = union_array_def_use_table_semnode(module,
                                               dt,
                                               tmp);
        free_all_array_def_use_table_semnode(tmp);
    }

    return dt;
}
