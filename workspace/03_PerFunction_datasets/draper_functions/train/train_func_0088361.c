get_first_block_in_set(Block *block_head, Block *block, IntSet succ)
{
    int i, j;
    Block *bpt;
    Stasche_mts_table *mts;
    Stasche_pc_info *pc;
    List *head = NULL;

    for (i = 1; i <= current_stasche_table->mts_num; i++) {
        if (in_IntSet(current_stasche_table->mts_info->mt[i], block->no)) {
            mts = current_stasche_table->mts[i];
            for (j = 0; j < mts->pc_num; j++) {
                for (pc = mts->pc_info[j]; pc != NULL; pc = pc->next) {
                    if (in_IntSet(succ, pc->mt_number)) {
                        bpt = search_block_from_no(block_head, pc->mt_number);
                        head = list_append(head, bpt);
                        break;
                    }
                }
            }
        }
    }

    return head;
}
