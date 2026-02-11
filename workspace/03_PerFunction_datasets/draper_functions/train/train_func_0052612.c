convert_copy_loop_to_dt_module()
{
    Module_table *mpt;

    if (!cmp_copy_loop_to_dt) return ;
    for (mpt = module_head; mpt != NULL; mpt = mpt->next) {
        convert_copy_loop_to_dt_blocks(mpt->block_head);
    }
}
