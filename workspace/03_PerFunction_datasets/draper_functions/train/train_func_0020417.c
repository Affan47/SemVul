mp_super_sb_extension(Module_table *mhead)
{
    Module_table *mpt;

    init_org_mdl_set();

    for (mpt = mhead ; mpt != NULL ; mpt = mpt->next) {
        if (mpt->kind != MODULE_BLOCKDATA) {
            super_hmdf_packing(mpt);
        }
    }

    super_sb_extension(mhead->block_head);
    set_flg_false();


    for (mpt = mhead ; mpt != NULL ; mpt = mpt->next) {
        if (mpt->kind != MODULE_BLOCKDATA) {
            one_module_on_one_super_hmdf(mpt);
            select_fosterage_hmdf(mpt->super_hmdf);
            eliminate_call_block_hmdf(mpt->super_hmdf);
        }
    }

}
