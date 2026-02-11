set_array_production(Block *bpt, Array_def_use_table_semnode *production)
{
    if (bpt->array_info->Production != NULL) {
        free_all_array_def_use_table_semnode(bpt->array_info->Production);
    }
    bpt->array_info->Production = production;
}
