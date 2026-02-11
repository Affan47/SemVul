unlink_sub_loop_var(Block *block_head)
{
    Block *bpt;
    for (bpt = block_head; bpt != NULL; bpt = bpt->next) {
        unlink_sub_loop_var_pe_stm(bpt->pre_head);
        if (bpt->inner != NULL) {
            unlink_sub_loop_var(bpt->inner);
        }
        unlink_sub_loop_var_pe_stm(bpt->post_head);
    }
}
