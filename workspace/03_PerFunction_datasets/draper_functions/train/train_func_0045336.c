search_const_module(Module_table *module, IntSet const_set, int *conv_table)
{
    if (module == NULL) {
        return;
    }

    foreach_const_nt_elem_table(module->nt_elem_head, const_set, conv_table,
                                search_const_semtree);
    foreach_const_dtu_trans_group(module->dtu_group_head, const_set, conv_table,
                                  search_const_semtree);
}
