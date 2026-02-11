change_const_to_var_next(Block         *block_head,
                         Var_table     *vpt,
                         int           entry)
{
    Block       *bpt;

    bpt = block_head;
    while (bpt != NULL) {
        change_const_to_var(bpt, vpt, entry);
        bpt = bpt->next;
    }
}
