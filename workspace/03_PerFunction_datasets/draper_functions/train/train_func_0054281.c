mtgen(Module_table *mhead)
{
    Block   *bpt;
    Module_table    *mpt;
    Hmdf_table *hhead;

    cfa(mhead);
    for (mpt=mhead ; mpt != NULL ; mpt=mpt->next) {
        if (mpt->kind != MODULE_BLOCKDATA) {
            if (mpt->super_hmdf == NULL) {
                fatal("NULL 'super_hmdf' found.\n");
            }
            hhead = eliminate_hmdf_at_call(mpt->super_hmdf->children);
            mpt->super_hmdf->children = hhead;

            bpt = mpt->block_head;
            make_exit_table(bpt);
            set_mt_usage(bpt);
            insert_mtjmp_and_exitmt(hhead, mpt);
            replace_jmp_mt_end(bpt, mpt);
            sense_blocks_to_split_mtjumps(bpt);
	    remove_last_jump(module_head);
#ifdef DEBUG
            print_exit(stderr, bpt, 1000);
#endif
	}
    }
    check_interlink(mhead);
    cfa(mhead);
}
