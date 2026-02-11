foreach_statement_blocks(Block *b_head,
                        void (*func)(Statement *stm, void *func_param),
                        void *param)
{
    Block *bpt;

    for (bpt = b_head; bpt != NULL; bpt = bpt->next) {
        foreach_statement_pes(bpt->pre_head, func, param);
        if (bpt->inner != NULL) {
            foreach_statement_blocks(bpt->inner, func, param);
        }
        foreach_statement_pes(bpt->post_head, func, param);
    }
}
