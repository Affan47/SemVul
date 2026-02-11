rename_mem_kind_array_entry(Stasche_table *spt,
                            int proc_num,
                            int org_amax,
                            memory_kind mem_kind)
{
    int i, j;
    Block *head = spt->hmdf->block->inner;
    Module_table *module = head->module;

    for (i = 0; i < proc_num; i++) {
        for (j = 1; j <= spt->mts_num; j++) {
            Stasche_pc_info *pc;
            List *blk_list;

            pc = spt->mts[j]->pc_info[i];
            blk_list = make_block_list_execed_on_pg(head, pc);
            rename_mem_kind_array_entry_block_list(blk_list, module,
                                                   proc_num, i,
                                                   org_amax, mem_kind);
        }
    }
}
