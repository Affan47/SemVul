set_acc_no_used_in_block(IntSet acc_no_set,
                         Block *block)
{
    Block *bpt;

    if (block->hmdf != NULL
        && block->hmdf->scheduling == SCHE_STATIC) {
        Hetero_stasche_acc_table *acc;
        int i, acc_no;
        int acc_num = (acc_stasche_head != NULL) ?
            acc_stasche_head->acc_num : 0;
        int mtg_id = block->hmdf->mtg_id;

        for (acc_no = 0; acc_no < acc_num; acc_no++) {
            for (acc = acc_stasche_head->acc[acc_no];
                 acc != NULL;
                 acc = acc->next) {
                for (i = 0; i < acc->mtg_num; i++) {
                    if (acc->mtg_id[i] == mtg_id) {
                        add1_IntSet(acc_no_set, acc_no);

                        break;
                    }
                }

                if (i < acc->mtg_num)
                    break;
            }
        }
    }

    if (block->kind == SB) {
        Module_table *mpt = search_module_for_sb(block);
        set_acc_no_used_in_block(acc_no_set, mpt->block_head);
    }

    for (bpt = block->inner; bpt != NULL; bpt = bpt->next)
        set_acc_no_used_in_block(acc_no_set, bpt);
}
