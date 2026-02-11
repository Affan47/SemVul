delete_nested_acc_block_for_blocks(Block *head, int acc_id)
{
    Block *bpt;

    for (bpt = head; bpt != NULL; bpt = bpt->next) {
        if (block_is_accelerator_task(bpt, acc_id)
            && (is_inner_of_acc_block(bpt)
                || module_is_called_from_acc_block(bpt->module))) {
#ifdef DEBUG_HETERO_HMDF
            fprintf(stderr,
                    "Hetero Directive Is Ignored.(Module:%s Block:%d)\n",
                    bpt->module->name, bpt->no);
#endif
            delete_hetero_directive(bpt);
        }
        if (bpt->inner) {
            delete_nested_acc_block_for_blocks(bpt->inner, acc_id);
        }
    }
}
