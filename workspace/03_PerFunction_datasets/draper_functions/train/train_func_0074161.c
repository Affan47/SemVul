append_common_dec_of_callee_to_caller_module(Common_table *chead, Module_table *mhead)
{
    Module_table *m;
    List *sblist, *li;
    int maxdepth = search_maxdepth(mhead);
    int i;
    Block *sb_block;

    for (i = maxdepth; i >= 0; i--) {
        for (m = mhead; m != NULL; m = m->next) {
            if (m->maxdepth == i) {
                sblist = get_sb_block_list(m->block_head, MODULE_FUNC);
                for (li = sblist; li != NULL; li = li->next) {
                    sb_block = li->data;
                    append_common_dec_of_callee_to_caller(m,
                                                          sb_callee(sb_block),
                                                          mhead,
                                                          chead);
                }
                sblist = get_sb_block_list(m->block_head, MODULE_SUB);
                for (li = sblist; li != NULL; li = li->next) {
                    sb_block = li->data;
                    append_common_dec_of_callee_to_caller(m,
                                                          sb_callee(sb_block),
                                                          mhead,
                                                          chead);
                }
            }
        }
    }
}
