append_new_dir_to_block(Block *block, Directive *dir)
{
    Directive *dpt;
    Directive *dpt_next;
    dpt = dir;
    while (dpt != NULL) {
        dpt_next = dpt->next;
        dpt->prev = dpt->next = NULL;
        if (!block_already_has_assign_acc_dir(block, dpt)) {
            if (block->dir_pre_head == NULL) {
                block->dir_pre_head = dir;
            } else {
                for (dpt = block->dir_pre_head; dpt->next != NULL; dpt = dpt->next);
                dpt->next = dir;
            }
        }
        dpt = dpt_next;
    }
}
